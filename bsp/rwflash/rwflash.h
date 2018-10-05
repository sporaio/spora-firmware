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
 *  \file       rwflash.h
 *  \brief      This module handle Read/Write Internal Flash Memory.
 *
 *  \ingroup    rwflash
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
#ifndef __RWFLASH_H__
#define __RWFLASH_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "sporacfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define FLASH_SIZE          (FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT * \
                                 FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE)

#define RWFLASH_SIZE        FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
#define RWFLASH_START       (FLASH_SIZE-RWFLASH_SIZE)
#define RWFLASH_END         (void *)(RWFLASH_START+sizeof(RWFlash))

#define RWFLASH_CRC_START   (void *)(RWFLASH_START)
#define RWFLASH_DATA_START  (void *)((RWFLASH_START + offsetof(RWFlash, cfg)))

#define RomRWFlash           ((RWFlash *)(RWFLASH_START))
    
/* ------------------------------- Data types ------------------------------ */
typedef unsigned short RWFlashCRC;

typedef struct 
{
    RWFlashCRC crc;
    SporaCfg cfg;
} __attribute__((aligned(4),packed)) RWFlash;
    
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
bool rwflash_init(void);
bool rwflash_verify(void **p);
bool rwflash_program(void *p, uint32_t len);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */

