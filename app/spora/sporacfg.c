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
 *  \file       sporacfg.c
 *  \brief      This module handle configuration message an settings.
 *
 *  \ingroup    sporaCfg
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
#include "fsl_common.h"
#include "sporacfg.h"
#include "rwflash.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static void *pCfg;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
setDefaults(SporaCfg *p)
{
    memset(p, 0, sizeof(SporaCfg));

    p->motionThr = MOTION_THR_DFT;

    if (sizeof(USER_NAME_DFT) > MAX_NAME_SIZE)
    	memcpy(p->name, USER_NAME_DFT, MAX_NAME_SIZE);
    else
    	memcpy(p->name, USER_NAME_DFT, sizeof(USER_NAME_DFT));
}



/* ---------------------------- Global functions --------------------------- */
void
spora_initCfg(void)
{
    rwflash_init(); 

    if (rwflash_verify(&pCfg) != true)
    {
        setDefaults(pCfg);

        RKH_DIS_INTERRUPT();
        rwflash_program(pCfg, sizeof(SporaCfg));
        RKH_ENA_INTERRUPT();
    }
}

void
spora_getCfg(SporaCfg *p)
{
    *p = *(SporaCfg *)pCfg;
}

uint8_t
spora_getCfg_motionThr(void)
{
    return ((SporaCfg *)(pCfg))->motionThr;
}

char *
spora_getCfg_name(void)
{
    return ((SporaCfg *)(pCfg))->name;
}

void
spora_setCfg(SporaCfg *p)
{
	RKH_DIS_INTERRUPT();

    if (rwflash_program(p, sizeof(SporaCfg)) != true)
    {
        if( rwflash_verify(&pCfg) != true )
        {
            setDefaults(pCfg);
        }
    }

    RKH_ENA_INTERRUPT();
}

/* ------------------------------ End of file ------------------------------ */
