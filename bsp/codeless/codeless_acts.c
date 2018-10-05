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
 *  \file       codeless_act.c
 *  \brief      Murata BLE Codeless AT command SSP´ actions routines.
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

#include <stdio.h>
#include <stdlib.h>
#include "rkh.h"
#include "spora.h"
#include "sporacfg.h"
#include "blemgr.h"
#include "jRead.h"
#include "codeless_acts.h"
#include "codeless_cmd.h"
#include "codeless_tree.h"

/* ----------------------------- Local macros ------------------------------ */
#define rxBufferEnd     (rxBuffer+sizeof(rxBuffer)/sizeof(char)-1)

/* ------------------------------- Constants ------------------------------- */
#define CLESS_RXBUFF_SIZE   50

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
#if defined(RKH_USE_TRC_SENDER)
static rui8_t ssp;
#endif

static char rxBuffer[CLESS_RXBUFF_SIZE];
static char *prx;

static RKH_ROM_STATIC_EVENT(e_cmdOk, evOk);
static RKH_ROM_STATIC_EVENT(e_sporaGetCfg, evSporaGetCfg);
static RKH_ROM_STATIC_EVENT(e_sporaGetData, evSporaGetData);
static RKH_STATIC_EVENT(e_cmdResp, evOk);
static evtCfg e_cfg;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
codeless_sspInit(void)
{
	ssp_init(&root);
    prx = rxBuffer;
}

void
cmdOk(unsigned char pos)
{
    RKH_SMA_POST_FIFO(bleMgr, &e_cmdOk, &ssp);
    codeless_stopCmdTimer();
}

void
cmdError(unsigned char pos)
{
    RKH_SMA_POST_FIFO(bleMgr, &e_cmdOk, &ssp);
    codeless_stopCmdTimer();
}

void
rPrintOk(unsigned char pos)
{
    RKH_SMA_POST_FIFO(bleMgr, &e_cmdOk, &ssp);
    codeless_stopCmdTimer();
}

void
gapStatusCollect(unsigned char data)
{
    if(prx < rxBufferEnd)
        *prx++ = data;
}

void
gapStatusOk(unsigned char data)
{
    codeless_stopCmdTimer();

    prx = rxBuffer;

    if( *(prx + GAP_CONNSTAT_OFFSET) == GAP_CONNECTED )
    {
        RKH_SET_STATIC_EVENT(&e_cmdResp, evConnected);
    }
    else
    {
        RKH_SET_STATIC_EVENT(&e_cmdResp, evDisconnected);
    }

    RKH_SMA_POST_FIFO(spora, &e_cmdResp, &ssp);
    RKH_SMA_POST_FIFO(bleMgr, &e_cmdOk, &ssp);
}

void
rcvCollect(unsigned char data)
{
    if(prx < rxBufferEnd)
    {
        *prx++ = data;
    }
    else
    {
    	codeless_sspInit();
    }
}

void
rcvChgJSonSep(unsigned char data )
{
	*(prx-1) = ',';
}

void
rcvOk(unsigned char data)
{
    *prx = '\0';
    prx = rxBuffer;

    switch(jRead_int(rxBuffer, "{'cmd'", NULL))
    {
        case SporaConfig:
            RKH_SET_STATIC_EVENT(&e_cfg, evSporaCfg);
            e_cfg.cfg.motionThr = jRead_int(rxBuffer, "{'h'", NULL); 
            jRead_string( rxBuffer, "{'n'", e_cfg.cfg.name, MAX_NAME_SIZE+1, NULL);

            RKH_SMA_POST_FIFO(spora, CE(&e_cfg), &ssp);
            break;

        case SporaGetConfig: 
            RKH_SMA_POST_FIFO(spora, CE(&e_sporaGetCfg), &ssp);
            break;

        case SporaGetData: 
            RKH_SMA_POST_FIFO(spora, CE(&e_sporaGetData), &ssp);
            break;

        default:
            break;
    }


}

/* ------------------------------ End of file ------------------------------ */
