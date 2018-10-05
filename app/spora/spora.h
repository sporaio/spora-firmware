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
 *  \file       spora.h
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
/* --------------------------------- Module -------------------------------- */
#ifndef __SPORA_H__
#define __SPORA_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "mpu9250.h"
#include "sporaCfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ................................ Signals ................................ */
typedef enum Signals
{
	evInitTout,
	evCmdTout,
    evFailureToggle,
    evConnStatusTout,
    evUnlikedTout,
    evMotionIndicatorTout,
    evConnected,
    evDisconnected,
    evOk,
    evError,
    evStartAdvertising,
    evStopAdvertising,
    evPushbuttonShortPress,
    evPushbuttonLongPress,
    evForceDisconnect,
    evMotionDetect,
    evSporaCfg,
    evSporaGetCfg,
    evSporaGetData,

	SPORA_NUM_EVENTS
}Signals;

/* ........................ Declares active object ......................... */
RKH_SMA_DCLR(spora);

/* ------------------------------- Data types ------------------------------ */
typedef enum
{
    SporaAck,
    SporaData,
    SporaGetData,
    SporaConfig,
    SporaGetConfig
}SporaCommand;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t mx;
    int16_t my;
    int16_t mz;
    int16_t temp;
    uint32_t time;
}SporaPacket;

typedef struct
{
	RKH_EVT_T e;
    SporaPacket data;
} evtMotion;

typedef struct
{
	RKH_EVT_T e;
    SporaCfg cfg;
} evtCfg;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
