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
 *  \file       mpu9250.c
 *  \brief      MPU9250 device routines.
 *
 *  \ingroup    bsp_test
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
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "bsp.h"
#include "mpu9250.h"
#include "spora.h"
#include "emafilter.h"
#include "sporacfg.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
#if defined(RKH_USE_TRC_SENDER)
static rui8_t mpu9250;
#endif

static evtMotion e_motion;
static uint8_t sampleRateCnt;
static bool running = false;
static Mpu9250Data samplerData;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
EXT_WAKE_UP_irqEnable(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinInterruptConfig(EXT_WAKE_UP_PORT,
                               EXT_WAKE_UP_GPIO_PIN,
							   kPORT_InterruptLogicOne);

    EnableIRQ(EXT_WAKE_UP_IRQ);
    NVIC_SetPriority(EXT_WAKE_UP_IRQ, RKH_PORT_IRQ_PRIO);

    GPIO_PinInit(EXT_WAKE_UP_GPIO,
                 EXT_WAKE_UP_GPIO_PIN,
                 &gpio_config);
}

static void
EXT_WAKE_UP_irqDisable(void)
{
    DisableIRQ(EXT_WAKE_UP_IRQ);
}

static
void
setMotionIRQ(uint8_t motionThr, uint8_t freq)
{
    RKH_ENTER_CRITICAL();

    EXT_WAKE_UP_irqDisable();

    /* Enter full-power accel-only mode, no FIFO/DMP. */    
    mpu9250_writeByte(USER_CTRL, 0);
    mpu9250_writeByte(PWR_MGMT_1, 0);
    mpu9250_writeByte(PWR_MGMT_2, BIT_STBY_XYZG);

    /* Setup Motion detection threshold */
    mpu9250_writeByte(WOM_THR, motionThr);

    /* Set wake frequency. */
    mpu9250_writeByte(LP_ACCEL_ODR, freq);

    /* Enable motion interrupt. */
    mpu9250_writeByte(MOT_DETECT_CTRL, BITS_WOM_EN);

    /* Enable cycle mode. */
    mpu9250_writeByte(PWR_MGMT_1, BIT_LPA_CYCLE);

    /* Enable interrupt. */
    mpu9250_writeByte(INT_ENABLE, BIT_MOT_INT_EN);
     
    EXT_WAKE_UP_irqEnable();

    RKH_EXIT_CRITICAL();
}

/* ---------------------------- Global functions --------------------------- */
void
EXT_WAKE_UP_IRQ_Handler(void)
{
	uint8_t status;
    SporaPacket *p;

    GPIO_PortClearInterruptFlags(EXT_WAKE_UP_GPIO,
                                 1U << EXT_WAKE_UP_GPIO_PIN);

    if(!running)
        return;

    RKH_SET_STATIC_EVENT(&e_motion, evMotionDetect);

    /* 
     * For getting accelerometer latched values, first read 
     * output registers before interrupt acknowledge.
     */
    p = &e_motion.data;
    p->x = mpu9250_readByte(ACCEL_XOUT_H) << 8 |
            mpu9250_readByte(ACCEL_XOUT_L);
    
    p->y = mpu9250_readByte(ACCEL_YOUT_H) << 8 |
            mpu9250_readByte(ACCEL_YOUT_L);
    
    p->z = mpu9250_readByte(ACCEL_ZOUT_H) << 8 |
            mpu9250_readByte(ACCEL_ZOUT_L);

    p->mx = samplerData.mx;
    p->my = samplerData.my;
    p->mz = samplerData.mz;

    p->temp = samplerData.temp;

    p->time = bsp_getTimeSec(); 

    /* 
     * Now reads and verify interrupt source 
     */
    status = mpu9250_readByte(INT_STATUS);

    if((status & BIT_MOT_INT_EN) == 0)
    	return;

    RKH_SMA_POST_FIFO(spora, CE(&e_motion), &mpu9250);
}

void
mpu9250_sampler(void)
{
    uint8_t magnet;
    int16_t value;
    Mpu9250Data *p = &samplerData;

    if(!running)
        return;

    if(sampleRateCnt && --sampleRateCnt)
        return;

    sampleRateCnt = SAMPLE_RATE;

    p->ax = mpu9250_readByte(ACCEL_XOUT_H)<<8 | mpu9250_readByte(ACCEL_XOUT_L);
    p->ay = mpu9250_readByte(ACCEL_YOUT_H)<<8 | mpu9250_readByte(ACCEL_YOUT_L);
    p->az = mpu9250_readByte(ACCEL_ZOUT_H)<<8 | mpu9250_readByte(ACCEL_ZOUT_L);

    value = mpu9250_readByte(TEMP_OUT_H)<<8 | mpu9250_readByte(TEMP_OUT_L);
    p->temp = emaFilter_LowPass(value, p->temp, TEMP_EMA_ALPHA);

    magnet = ak8963_readByte(AK8963_ST1);

    if(magnet == 0x00)
        return;

    value = ak8963_readByte(AK8963_XOUT_H)<<8 | ak8963_readByte(AK8963_XOUT_L);
    p->mx = emaFilter_LowPass(value, p->mx, MAG_EMA_ALPHA);

    value = ak8963_readByte(AK8963_YOUT_H)<<8 | ak8963_readByte(AK8963_YOUT_L);
    p->my = emaFilter_LowPass(value, p->my, MAG_EMA_ALPHA);

    value = ak8963_readByte(AK8963_ZOUT_H)<<8 | ak8963_readByte(AK8963_ZOUT_L);
    p->mz = emaFilter_LowPass(value, p->mz, MAG_EMA_ALPHA);

    ak8963_writeByte(AK8963_CNTL, 0x11);
}

Mpu9250Data *
mpu9250_getSamplerData(void)
{
    return &samplerData;
}

bool
mpu9250_init(void)
{
    static uint8_t aux;

    I2C_init();
    if (I2C_readAccelWhoAmI(WHO_AM_I_MPU9250, MPU9250_WHOAMI) != true)
    {
        return false;
    }

    /* MPU reset */
    mpu9250_writeByte( PWR_MGMT_1, 0x80 );

    BSP_MSLEEP(MPU9250_RESET_TIME);

    aux = mpu9250_readByte(INT_STATUS);
    /* MPU general settings */
    /* settup accelerometers range */
    mpu9250_writeByte(ACCEL_CONFIG, ACC_FULL_SCALE_16_G);

    /*
     * INT Pin/Bypass:
     *      - bit 1 I2C bypass mode enable.
     *      - bit 5 active until read.
     */
    aux = mpu9250_readByte(INT_PIN_CFG);
    aux |= 0x22;
    mpu9250_writeByte(INT_PIN_CFG, aux);

    /* Test AK8963 reading Who am I */
    aux = ak8963_readByte(WHO_AM_I_AK8963);

    /* Sets magnetometer in 16bit continuos mode */
    ak8963_writeByte(AK8963_CNTL, 0x11);

    setMotionIRQ(spora_getCfg_motionThr(), INV_LPA_80HZ);

    running = true;
    sampleRateCnt = SAMPLE_RATE;

    return true;
}

void
mpu9250_setMotionThreshold(uint8_t th)
{
    setMotionIRQ(th, INV_LPA_80HZ);
}

/* ------------------------------ End of file ------------------------------ */
