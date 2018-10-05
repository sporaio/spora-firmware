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
 *  \file       codeless.c
 *  \brief      Murata BLE Codeless routines.
 *
 *  \ingroup    ble
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.01.5  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "fsl_lpuart.h"
#include "bsp.h"
#include "ssp.h"
#include "rkh.h"
#include "spora.h"
#include "blemgr.h"
#include "codeless.h"
#include "codeless_acts.h"
#include "codeless_cmd.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_ROM_STATIC_EVENT(e_CmdTout, evCmdTout);
static RKH_TMR_T cmdTout;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
codeless_init(void)
{
    bsp_uartInit();
    codeless_sspInit();
    RKH_TMR_INIT(&cmdTout, &e_CmdTout, NULL);
}

void
codeless_stopCmdTimer(void)
{
    rkh_tmr_stop(&cmdTout);
}

void
codeless_sync(void)
{
    bsp_uartPutstring(ClessSync.cmd);
    RKH_TMR_ONESHOT(&cmdTout, bleMgr, ClessSync.tout);
}

void
codeless_reset(void)
{
    bsp_uartPutstring(ClessReset.cmd);
    RKH_TMR_ONESHOT(&cmdTout, bleMgr, ClessReset.tout);
}

void
codeless_getGapStatus(void)
{
    bsp_uartPutstring(ClessGapStatus.cmd);
    RKH_TMR_ONESHOT(&cmdTout, bleMgr, ClessGapStatus.tout);
}

void
codeless_advertisingStart(void)
{
    bsp_uartPutstring(ClessAdvStart.cmd);
    RKH_TMR_ONESHOT(&cmdTout, bleMgr, ClessAdvStart.tout);
}

void
codeless_advertisingStop(void)
{
    bsp_uartPutstring(ClessAdvStop.cmd);
    RKH_TMR_ONESHOT(&cmdTout, bleMgr, ClessAdvStop.tout);
}

void
codeless_gapDisconnect(void)
{
    bsp_uartPutstring(ClessDisconnect.cmd);
}

void codeless_sendData(char *p)
{
    bsp_uartPutstring(ClessSendData.cmd);
    bsp_uartPutstring(p);
    bsp_uartPutstring(SPORA_TX_MSJ_END);
    bsp_uartPutchar('\r');
}

/* ------------------------------ End of file ------------------------------ */
