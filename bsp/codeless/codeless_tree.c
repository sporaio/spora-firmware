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
 *  \file       codelesstree.h
 *  \brief      Murata BLE Codeless AT command SSP´ tree.
 *
 *  \ingroup    codeless
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
#include <stdlib.h>
#include "codeless_tree.h"
#include "codeless_acts.h"
#include "codeless_cmd.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
SSP_CREATE_NORMAL_NODE(root);
SSP_CREATE_BR_TABLE(root)
	SSPBR("AT",              NULL,   &at),
	SSPBR(SPORA_RX_MSJ_START, NULL,   &rcv),
SSP_END_BR_TABLE

/*
 * AT
 */
SSP_CREATE_NORMAL_NODE(at);
SSP_CREATE_BR_TABLE(at)
	SSPBR("+",     NULL,   &atPlus),
	SSPBR("r",     NULL,   &atr),
	SSPBR(CODELESS_OK,     cmdOk,     &root),
	SSPBR(CODELESS_ERROR,  cmdError,  &root),
SSP_END_BR_TABLE

/*
 * AT+
 */
SSP_CREATE_NORMAL_NODE(atPlus);
SSP_CREATE_BR_TABLE(atPlus)
	SSPBR("GAPSTATUS\r\n", NULL,      &gapStatus),
	SSPBR(CODELESS_OK,     cmdOk,     &root),
	SSPBR(CODELESS_ERROR,  cmdError,  &root),
SSP_END_BR_TABLE

/*
 * ATr
 */
SSP_CREATE_NORMAL_NODE(atr);
SSP_CREATE_BR_TABLE(atr)
	SSPBR("+PRINT=",        NULL,       &rPrint),
	SSPBR(CODELESS_OK,      cmdOk,      &root),
	SSPBR(CODELESS_ERROR,   cmdError,   &root),
SSP_END_BR_TABLE

/*
 * ATr+PRINT
 */
SSP_CREATE_TRN_NODE(rPrint, NULL);
SSP_CREATE_BR_TABLE(rPrint)
	SSPBR(SPORA_TX_MSJ_END,  rPrintOk,    &root),
	SSPBR(CODELESS_ERROR,    cmdError,    &root),
SSP_END_BR_TABLE

/*
 * AT+GAPSTATUS
 */
SSP_CREATE_TRN_NODE(gapStatus, gapStatusCollect);
SSP_CREATE_BR_TABLE(gapStatus)
	SSPBR(CODELESS_OK,     gapStatusOk, &root),
	SSPBR(CODELESS_ERROR,  cmdError,    &root),
SSP_END_BR_TABLE

/*
 * +RCV
 */
SSP_CREATE_TRN_NODE(rcv, rcvCollect);
SSP_CREATE_BR_TABLE(rcv)
	SSPBR(";", rcvChgJSonSep,  &rcv),
	SSPBR(SPORA_RX_MSJ_END, rcvOk,  &root),
SSP_END_BR_TABLE

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
