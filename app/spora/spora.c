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
 *  \file       spora.c
 *  \brief      Spora demo.
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
#include <stdio.h>

#include "jwrite.h"
#include "rkh.h"
#include "bleMgr.h"
#include "spora.h"
#include "sporacfg.h"
#include "codeless.h"
#include "codeless_cmd.h"
#include "mpu9250.h"
#include "pushbutton.h"
#include "battery.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define UNLINKED_TIMEOUT        RKH_TIME_SEC(60)
#define MOTION_DET_TIME         RKH_TIME_MS(3000)

#define SPORA_PACKET_FORMAT(m,buff,button) \
        {   \
            sprintf(buff, "%lu,%i,%i,%i,%i,%i,%i,%i,%x,%x,%s,%s", \
                            m.time,                     \
                            m.x, m.y, m.z,              \
                            m.mx, m.my, m.mz,           \
                            m.temp,                     \
                            button,                     \
                            spora_getCfg_motionThr(),   \
                            spora_getCfg_name(),        \
                            SPORA_TX_MSJ_END);          \
        }

typedef enum
{
    RELEASE,
    PRESS
}PushButton_t;

/* ......................... Declares active object ........................ */
typedef struct Spora Spora;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_COMP_STATE   steady; 
RKH_DCLR_BASIC_STATE  unlinked, linked, hiden, motionDetect; 
RKH_DCLR_SHIST_STATE  steadySHist;
static char jBuff[150];

/* ........................ Declares initial action ........................ */
static void init(Spora *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void setHiden(Spora *const me, RKH_EVT_T *pe);
static void setDiscoverable(Spora *const me, RKH_EVT_T *pe);
static void disconnect(Spora *const me, RKH_EVT_T *pe);
static void sendMotion(Spora *const me, RKH_EVT_T *pe);
static void sendButton(Spora *const me, RKH_EVT_T *pe);
static void updateCfg(Spora *const me, RKH_EVT_T *pe);
static void sendCfg(Spora *const me, RKH_EVT_T *pe);
static void sendData(Spora *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void unlinkedEntry(Spora *const me);
static void linkStatusOn(Spora *const me);
static void onMotion(Spora *const me);
static void battStatEnable(Spora *const me);

/* ......................... Declares exit actions ......................... */
static void unlinkedExit(Spora *const me);
static void linkStatusOff(Spora *const me);
static void offMotion(Spora *const me);
static void battStatDisable(Spora *const me);

/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_COMP_STATE(steady, NULL, NULL, RKH_ROOT, &unlinked, &steadySHist);
RKH_CREATE_TRANS_TABLE(steady)
    RKH_TRINT(evSporaCfg, NULL, &updateCfg),
    RKH_TRINT(evSporaGetCfg, NULL, &sendCfg),
    RKH_TRREG(evMotionDetect, NULL, NULL, &motionDetect),
RKH_END_TRANS_TABLE

RKH_CREATE_SHALLOW_HISTORY_STATE(steadySHist, &steady, NULL, NULL, NULL);

RKH_CREATE_BASIC_STATE(unlinked, unlinkedEntry, unlinkedExit, &steady, NULL);
RKH_CREATE_TRANS_TABLE(unlinked)
    RKH_TRREG(evUnlikedTout, NULL, setHiden, &hiden),
    RKH_TRREG(evPushbuttonLongPress, NULL, setHiden, &hiden),
    RKH_TRREG(evConnected, NULL, NULL, &linked),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(hiden, battStatEnable, battStatDisable, &steady, NULL);
RKH_CREATE_TRANS_TABLE(hiden)
    RKH_TRREG(evPushbuttonLongPress, NULL, setDiscoverable, &unlinked),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(linked, linkStatusOn, linkStatusOff, &steady, NULL);
RKH_CREATE_TRANS_TABLE(linked)
    RKH_TRINT(evSporaGetData, NULL, &sendData),
    RKH_TRREG(evMotionDetect, NULL, sendMotion, &motionDetect),
    RKH_TRREG(evDisconnected, NULL, NULL, &unlinked),
    RKH_TRREG(evPushbuttonLongPress, NULL, disconnect, &unlinked),
    RKH_TRREG(evPushbuttonShortPress, NULL, sendButton, &motionDetect),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(motionDetect, onMotion, offMotion, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(motionDetect)
    RKH_TRINT(evSporaCfg, NULL, &updateCfg),
    RKH_TRINT(evSporaGetCfg, NULL, &sendCfg),
    RKH_TRREG(evMotionIndicatorTout, NULL, NULL, &steadySHist),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Spora
{
    RKH_SMA_T sma;
    RKH_TMR_T tmr;
};

RKH_SMA_CREATE(Spora, spora, 0, HCAL, &unlinked, init, NULL);
RKH_SMA_DEF_PTR(spora);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_STATIC_EVENT(e_tmr, evInitTout);
static RKH_ROM_STATIC_EVENT(e_startAdvertising, evStartAdvertising);
static RKH_ROM_STATIC_EVENT(e_stopAdvertising, evStopAdvertising);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
char *
formatSporaData(SporaPacket *p, PushButton_t bst)
{
	jwOpen( jBuff, sizeof(jBuff), JW_OBJECT, JW_COMPACT );
    jwObj_int( "cmd", SporaData );
    jwObj_int( "t", p->time );
    jwObj_int( "x", p->x );
    jwObj_int( "y", p->y );
    jwObj_int( "z", p->z );
    jwObj_int( "u", p->mx );
    jwObj_int( "v", p->my );
    jwObj_int( "w", p->mz );
    jwObj_int( "c", p->temp );
    jwObj_int( "b", bst );
    jwObj_int( "h", spora_getCfg_motionThr() );
    jwObj_string( "n", spora_getCfg_name() );
    jwClose();

    return jBuff;
}

static
char *
formatSporaAck(void)
{
	jwOpen( jBuff, sizeof(jBuff), JW_OBJECT, JW_COMPACT );
    jwObj_int( "cmd", SporaAck );
    jwClose();

    return jBuff;
}

static
char *
formatSporaCfg(void)
{
	jwOpen( jBuff, sizeof(jBuff), JW_OBJECT, JW_COMPACT );
    jwObj_int( "cmd", SporaConfig );
    jwObj_int( "h", spora_getCfg_motionThr() );
    jwObj_string( "n", spora_getCfg_name() );
    jwClose();

    return jBuff;
}

/* ............................ Initial action ............................. */
static void
init(Spora *const me, RKH_EVT_T *pe)
{
    spora_initCfg();

    pushbutton_init();
    mpu9250_init();
    battery_init();
    RKH_TMR_INIT(&me->tmr, &e_tmr, NULL);
}

/* ............................ Effect actions ............................. */
static void
setHiden(Spora *const me, RKH_EVT_T *pe)
{
    RKH_SMA_POST_FIFO(bleMgr, &e_stopAdvertising, &spora);
}

static void
setDiscoverable(Spora *const me, RKH_EVT_T *pe)
{
    RKH_SMA_POST_FIFO(bleMgr, &e_startAdvertising, &spora);
}

static void
disconnect(Spora *const me, RKH_EVT_T *pe)
{
    codeless_gapDisconnect();
}

static void
sendMotion(Spora *const me, RKH_EVT_T *pe)
{
    evtMotion *m = (evtMotion *)(pe);

    codeless_sendData(formatSporaData(&m->data, RELEASE));
}

static void
sendButton(Spora *const me, RKH_EVT_T *pe)
{
    static SporaPacket packet;
    Mpu9250Data *q;
    
    q = mpu9250_getSamplerData();

    packet.x = q->ax;
    packet.y = q->ay;
    packet.z = q->az;
    packet.mx = q->mx;
    packet.my = q->my;
    packet.mz = q->mz;
    packet.temp = q->temp;
    packet.time = bsp_getTimeSec();

    codeless_sendData(formatSporaData(&packet, PRESS));
}

static void
updateCfg(Spora *const me, RKH_EVT_T *pe)
{
    evtCfg *p = (evtCfg *)(pe);

    spora_setCfg(&p->cfg);
    mpu9250_setMotionThreshold(p->cfg.motionThr);    

    codeless_sendData(formatSporaAck());
}

static void
sendCfg(Spora *const me, RKH_EVT_T *pe)
{
    codeless_sendData(formatSporaCfg());
}

static void
sendData(Spora *const me, RKH_EVT_T *pe)
{
    static SporaPacket packet;
    Mpu9250Data *q;
    
    q = mpu9250_getSamplerData();

    packet.x = q->ax;
    packet.y = q->ay;
    packet.z = q->az;
    packet.mx = q->mx;
    packet.my = q->my;
    packet.mz = q->mz;
    packet.temp = q->temp;
    packet.time = bsp_getTimeSec();

    codeless_sendData(formatSporaData(&packet, RELEASE));
}

/* ............................. Entry actions ............................. */
static void
unlinkedEntry(Spora *const me)
{
	battery_statusEnable(bleInScan);
    RKH_SET_STATIC_EVENT(&e_tmr, evUnlikedTout);
    RKH_TMR_ONESHOT(&me->tmr, spora, UNLINKED_TIMEOUT);
}

static void
linkStatusOn(Spora *const me)
{
    bsp_setBleConnectionLed(true);
}

static void
onMotion(Spora *const me)
{
    bsp_setMotionLed(true);
    RKH_SET_STATIC_EVENT(&e_tmr, evMotionIndicatorTout);
    RKH_TMR_ONESHOT(&me->tmr, spora, MOTION_DET_TIME);
}

static void
battStatEnable(Spora *const me)
{
    battery_statusEnable(bleHiden);
}

/* ............................. Exit actions .............................. */
static void
unlinkedExit(Spora *const me)
{
    rkh_tmr_stop(&me->tmr); 
    battStatDisable(me);
}

static void
linkStatusOff(Spora *const me)
{
    bsp_setBleConnectionLed(false);
}

static void
offMotion(Spora *const me)
{
    bsp_setMotionLed(false);
    rkh_tmr_stop(&me->tmr); 
}

static void
battStatDisable(Spora *const me)
{
    battery_statusDisable();
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
