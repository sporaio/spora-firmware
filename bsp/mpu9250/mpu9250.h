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
 *  \file       mpu9250.h
 *  \brief      MPU9250 device routines.
 *
 *  \ingroup    bsp
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
#ifndef __MPU9250_H__
#define __MPU9250_H__

/* ----------------------------- Include files ----------------------------- */
#include "mpu9250_regs.h"
#include "i2c.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define TEMP_EMA_ALPHA  2
#define MAG_EMA_ALPHA   2
#define MPU9250_RESET_TIME     100
#define SAMPLE_RATE            RKH_TIME_MS(100)

/* ------------------------------- Data types ------------------------------ */
typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t mx;
    int16_t my;
    int16_t mz;
    int16_t temp;
}Mpu9250Data;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
bool mpu9250_init(void);
void mpu9250_sampler(void);
Mpu9250Data *mpu9250_getSamplerData(void);
void mpu9250_setMotionThreshold(uint8_t th);    

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
