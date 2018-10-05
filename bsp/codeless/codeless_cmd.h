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
 *  \file       codeless.h
 *  \brief      Murata BLE Codeless AT command definition.
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

/* --------------------------------- Module -------------------------------- */
#ifndef __CODELESS_CMD_H__
#define __CODELESS_CMD_H__

/* ----------------------------- Include files ----------------------------- */
#include "fsl_common.h"
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define CLESS_CMD_TBL(name)         const CodelessCmd name[] = {
#define CLESS_CMD(cmd,tout)         {(cmd), RKH_TIME_MS(tout)},
#define CLESS_CMD_ENDTBL            { NULL, 0 }}

/* -------------------------------- Constants ------------------------------ */
#define CODELESS_OK             "\r\nOK\r\n"
#define CODELESS_ERROR          "\r\nERROR\r\n"
#define GAP_CONNSTAT_OFFSET     2
#define GAP_CONNECTED           '1'    
#define SPORA_END_OF_MSJ        "\\EOSM"
#define SPORA_TX_MSJ_END        SPORA_END_OF_MSJ
#define SPORA_RX_MSJ_START      "+RCV="
#define SPORA_RX_MSJ_END        SPORA_TX_MSJ_END "\r\n"

/*
 * Codeless AT Command Table index
 */
typedef enum
{
    CLESS_SYNC,
    CLESS_RESET,
    CLESS_GSTATUS,
    CLESS_ADVSTOP,
    CLESS_ADVSTART,
    CLESS_DISCONNECT,
    CLESS_SEND,
    CLESS_CMDS
}CodelessCmdIx;

#define ClessSync        codelessCmdTbl[CLESS_SYNC]
#define ClessReset       codelessCmdTbl[CLESS_RESET]
#define ClessGapStatus   codelessCmdTbl[CLESS_GSTATUS]
#define ClessAdvStop     codelessCmdTbl[CLESS_ADVSTOP]
#define ClessAdvStart    codelessCmdTbl[CLESS_ADVSTART]
#define ClessDisconnect  codelessCmdTbl[CLESS_DISCONNECT]
#define ClessSendData    codelessCmdTbl[CLESS_SEND]

/* ------------------------------- Data types ------------------------------ */

typedef struct
{
	const char* cmd;
    unsigned char tout;
}CodelessCmd;

/* -------------------------- External variables --------------------------- */
extern const CodelessCmd codelessCmdTbl[];

/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
