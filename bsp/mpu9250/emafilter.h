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
 *  \file       emafilter.h
 *  \brief      Exponential Moving Average Filter routines.
 *
 *  \ingroup    EMA
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
#ifndef __EMAFILTER_H__
#define __EMAFILTER_H__

/* ----------------------------- Include files ----------------------------- */
#include "stdint.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/**
 *  \brief
 *  EMA Low Pass Filter
 *
 *  \param[in] new      New sample.
 *  \param[in] last     Last filtered value.
 *  \param[in] alph     Filtering hardness [1, 2, 4 ...],
 *                      as higher is alpha, filtering is harder.
 */
int16_t emaFilter_LowPass(int16_t new, int16_t last, uint8_t alpha);

/**
 *  \brief
 *  EMA High Pass Filter
 *
 *  \param[in] new      New sample.
 *  \param[in] last     Last filtered value.
 *  \param[in] alph     Filtering hardness [1, 2, 4 ...],
 *                      as higher is alpha, filtering is harder.
 */
int16_t emaFilter_HighPass(int16_t new, int16_t last, uint8_t alpha);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
