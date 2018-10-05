/*
 *  --------------------------------------------------------------------------
 *
 *                                    Spora
 *                                -------------
 *
 *                  Coin-sized programmable multi-sensor node
 *
 *                      Copyright (C) 2018  Enye Tech.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  Spora is an open-source, programmable multi-sensor node,
 *  specifically designed for wearables but with endless opportunities.
 *
 *  Spora is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  Spora is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  Spora web site: http://www.sporaio.com
 *  e-mail:         hello@sporaio.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       blemgr.c
 *  \brief      BLE Connection Manager.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.28  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña  db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "spora.h"
#include "blemgr.h"
#include "codeless.h"
#include "codeless_cmd.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define INIT_TIME               RKH_TIME_SEC(5)
#define DISCONNECTED_TIMEOUT    RKH_TIME_SEC(60)
#define CONNSTATUS_CHKTIME      RKH_TIME_SEC(1)
#define FAILURE_PERIOD          RKH_TIME_MS(200)

/* ......................... Declares active object ........................ */
typedef struct BleMgr BleMgr;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE waitSync, reseting, failure, 
                     idle, waitConnStatus, pause;

RKH_DCLR_COMP_STATE init, running;

/* ........................ Declares initial action ........................ */
static void bleInit(BleMgr *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void cmdTout(BleMgr *const me, RKH_EVT_T *pe);
static void sendReset(BleMgr *const me, RKH_EVT_T *pe);
static void sendGetConnStatus(BleMgr *const me, RKH_EVT_T *pe);
static void startAdvertising(BleMgr *const me, RKH_EVT_T *pe);
static void stopAdvertising(BleMgr *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void initEntry(BleMgr *const me);
static void sendSync(BleMgr *const me);
static void bleError(BleMgr *const me);
static void idleEntry(BleMgr *const me);

/* ......................... Declares exit actions ......................... */
static void initExit(BleMgr *const me);
static void idleExit(BleMgr *const me);

/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_COMP_REGION_STATE(init, initEntry, initExit,  RKH_ROOT, &waitSync,
                             NULL, RKH_NO_HISTORY, NULL, NULL, NULL, NULL );
RKH_CREATE_TRANS_TABLE(init)
    RKH_TRREG(evInitTout, NULL, NULL, &failure),
    RKH_TRREG(evCmdTout, NULL, NULL, &failure),
    RKH_TRREG(evOk, NULL, NULL, &running),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitSync, sendSync, NULL, &init, NULL);
RKH_CREATE_TRANS_TABLE(waitSync)
    RKH_TRINT(evCmdTout, NULL, sendSync),
    RKH_TRREG(evOk, NULL, sendReset, &reseting),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(reseting, NULL, NULL, &init, NULL);
RKH_CREATE_TRANS_TABLE(reseting)
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(failure, bleError, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(failure)
    RKH_TRREG(evFailureToggle, NULL, NULL, &failure),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_REGION_STATE(running, NULL, NULL, RKH_ROOT, &idle, NULL,
                             RKH_NO_HISTORY, NULL, NULL, NULL, NULL );
RKH_CREATE_TRANS_TABLE(running)
    RKH_TRREG(evStopAdvertising, NULL, stopAdvertising, &pause),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(idle, idleEntry, idleExit, &running, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRINT(evCmdTout, NULL, cmdTout),
    RKH_TRREG(evConnStatusTout, NULL, sendGetConnStatus, &waitConnStatus),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitConnStatus, NULL, NULL, &running, NULL);
RKH_CREATE_TRANS_TABLE(waitConnStatus)
    RKH_TRREG(evOk, NULL, NULL, &idle),
    RKH_TRREG(evCmdTout, NULL, cmdTout, &idle),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(pause, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(pause)
    RKH_TRREG(evStartAdvertising, NULL, startAdvertising, &running),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct BleMgr
{
    RKH_SMA_T sma;
    RKH_TMR_T tmr;
};

RKH_SMA_CREATE(BleMgr, bleMgr, 1, HCAL, &init, bleInit, NULL);
RKH_SMA_DEF_PTR(bleMgr);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_STATIC_EVENT(e_tmr, evInitTout);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
bleInit(BleMgr *const me, RKH_EVT_T *pe)
{
    RKH_TMR_INIT(&me->tmr, &e_tmr, NULL);

    codeless_init();
    bsp_bleReset(false);
}

/* ............................ Effect actions ............................. */
static void
cmdTout(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
        
    codeless_init();
//    BSP_MSLEEP(100);
}

static void
sendReset(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;
        
    codeless_reset();
}

static void
sendGetConnStatus(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    codeless_getGapStatus();
}

static void
stopAdvertising(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    codeless_advertisingStop();
}

static void
startAdvertising(BleMgr *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    codeless_advertisingStart();
}

/* ............................. Entry actions ............................. */
static void
initEntry(BleMgr *const me)
{
    RKH_TMR_ONESHOT(&me->tmr,  bleMgr, INIT_TIME);
}

static void
sendSync(BleMgr *const me)
{
    (void)me;
    codeless_sync();
}

static void
bleError(BleMgr *const me)
{
    (void)me;
    bsp_toggleBleFailureLed();
    RKH_SET_STATIC_EVENT(&e_tmr, evFailureToggle);
    RKH_TMR_ONESHOT(&me->tmr, bleMgr, FAILURE_PERIOD);
}

static void
idleEntry(BleMgr *const me)
{
    RKH_SET_STATIC_EVENT(&e_tmr, evConnStatusTout);
    RKH_TMR_ONESHOT(&me->tmr, bleMgr, CONNSTATUS_CHKTIME);
}

/* ............................. Exit actions .............................. */
static void
initExit(BleMgr *const me)
{
   rkh_tmr_stop(&me->tmr); 
}

static void
idleExit(BleMgr *const me)
{
    rkh_tmr_stop(&me->tmr);
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
