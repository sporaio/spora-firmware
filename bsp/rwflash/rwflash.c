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
 *  \file       rwflash.c
 *  \brief      This module handle Read/Write Internal Flash Memory.
 *
 *  \ingroup    rwflash
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
#include "fsl_flash.h"
#include "rwflash.h"
#include "sporacfg.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RWFlash RamRWFlash;
static flash_config_t mFlash;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
RWFlashCRC
getCRC(void *start, unsigned size)
{
    char *p;
    RWFlashCRC sum;

    for(p = start, sum = 0; p < (char *)(start) + size; ++p)
    {
        sum += *p;
    }

    return (~sum + 1);
}

/* ---------------------------- Global functions --------------------------- */
bool
rwflash_init(void)
{
    status_t result;
    flash_security_state_t securityStatus = kFLASH_SecurityStateNotSecure; 

    /* Clean up Flash driver Structure*/
    memset(&mFlash, 0, sizeof(flash_config_t));    

    /* Setup flash driver structure for device and initialize variables. */
    result = FLASH_Init(&mFlash);

    if (kStatus_FLASH_Success != result)
    {
        return false;
    }

    /* Check security status. */
    result = FLASH_GetSecurityState(&mFlash, &securityStatus);
    if (kStatus_FLASH_Success != result)
    {
        return false;
    }

    /* Test pflash basic opeation only if flash is unsecure. */    
    if (kFLASH_SecurityStateNotSecure != securityStatus)
    {
        return false;
    }
    
    return true;
}

bool
rwflash_verify(void **p)
{
    if (getCRC(RWFLASH_DATA_START, sizeof(SporaCfg)) != RomRWFlash->crc)
    {
        *p = &RamRWFlash.cfg;
        return false;
    }
    
    *p = &RomRWFlash->cfg;
    return true;
}

bool
rwflash_program(void *p, uint32_t len)
{
    status_t result; 
    uint32_t failAddr, failDat;    

    if(len > RWFLASH_SIZE)
        return false;
    
    if(p == NULL)
        return false;

    RamRWFlash.crc = getCRC(p, len);
    RamRWFlash.cfg = *(SporaCfg*)(p);

    result = FLASH_Erase(&mFlash, RWFLASH_START, RWFLASH_SIZE,
                                                   kFLASH_ApiEraseKey);
    if (kStatus_FLASH_Success != result)
    {
        return false;
    }

    result = FLASH_VerifyErase(&mFlash, RWFLASH_START, RWFLASH_SIZE,
                                                   kFLASH_MarginValueUser);
    if (kStatus_FLASH_Success != result)
    {
        return false;
    }
    
    result = FLASH_Program(&mFlash, RWFLASH_START, (uint32_t *)&RamRWFlash,
                                                    sizeof(RamRWFlash));
    if (kStatus_FLASH_Success != result)
    {
        return false;
    }

    result = FLASH_VerifyProgram(&mFlash, RWFLASH_START, sizeof(RWFlash),
    		       (const uint32_t *)&RamRWFlash, kFLASH_MarginValueUser,
                   &failAddr, &failDat);
    if (kStatus_FLASH_Success != result)
    {
        return false;
    } 

    return true;
}

/* ------------------------------ End of file ------------------------------ */
