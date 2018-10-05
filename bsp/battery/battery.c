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
 *  \file       battery.h
 *  \brief      Battery status and keep alive simple state machine.
 *
 *  \ingroup    battery
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
#include "rkh.h"
#include "bsp.h"
#include "fsl_gpio.h"
#include "battery.h"

/* ----------------------------- Local macros ------------------------------ */
#define pinRead()                GPIO_PinRead(BATTERY_STATUS_GPIO, \
                                             BATTERY_STATUS_GPIO_PIN)

#define SEQUENCE_TIMEOUT()       (sequenceTick && --sequenceTick== 0)
#define SEQUENCE_TIMER_RELOAD()  (sequenceTick = SEQUENCE_KEEPALIVE_TIME)

/* ------------------------------- Constants ------------------------------- */
typedef enum
{
    stIdle,
    stBattCharging,
    stSeqRed,
    stSeqGreen,
    stSeqBlue,
	stSeqOff,
    stDisabled
} BatteryState;

#define BATTERY_SAMPLE_TICK     RKH_TIME_MS(100)
#define SEQUENCE_KEEPALIVE_TIME (RKH_TIME_MS(10000)/BATTERY_SAMPLE_TICK)
 
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static unsigned char state;
static bool running = false;
static uint32_t sampleTick, sequenceTick;
static BleScanStatus currentBleScanStatus;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
battery_init(void)
{
    port_pin_config_t sw_port_config = {kPORT_PullUp,
                                        kPORT_SlowSlewRate,
                                        kPORT_PassiveFilterDisable,
                                        kPORT_LowDriveStrength,
                                        kPORT_MuxAsGpio};

    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinConfig(BATTERY_STATUS_PORT,
                      BATTERY_STATUS_GPIO_PIN,
                      &sw_port_config);

    GPIO_PinInit(BATTERY_STATUS_GPIO,
                 BATTERY_STATUS_GPIO_PIN,
                 &sw_config);

    state = stIdle;
    sampleTick = BATTERY_SAMPLE_TICK;
    sequenceTick = SEQUENCE_KEEPALIVE_TIME;
    currentBleScanStatus = bleInScan;
    running = true;
}

void
battery_sampler(void)
{
    if(!running)
        return;

    if(sampleTick != 0)
    {
        --sampleTick;
        return;
    }

    sampleTick = BATTERY_SAMPLE_TICK;

    switch(state)
    {
        case stIdle:
            bsp_setBatteryLed(false);

            state = (pinRead() == 0) ? stBattCharging : stIdle;

            if (SEQUENCE_TIMEOUT())
            {
                SEQUENCE_TIMER_RELOAD();
                bsp_setBatteryLed(false);

                state = (currentBleScanStatus == bleInScan) ? stSeqBlue : stSeqRed;
            }

            break;

        case stBattCharging:
            bsp_setBatteryLed(true);

            state = (pinRead() == 0) ? stBattCharging : stIdle;

            if (SEQUENCE_TIMEOUT())
            {
                SEQUENCE_TIMER_RELOAD();
                bsp_setBatteryLed(false);

                state = (currentBleScanStatus == bleInScan) ? stSeqBlue : stSeqRed;
            }

            break;

        case stSeqRed:
            bsp_setMotionLed(true);
            state = stSeqGreen;
            break;

        case stSeqGreen:
            bsp_setMotionLed(false);
            bsp_setBatteryLed(true);
            state = stSeqBlue;
            break;

        case stSeqBlue:
            bsp_setBatteryLed(false);
            bsp_setBleConnectionLed(true);
            state = stSeqOff;
            break;

        case stSeqOff:
            bsp_setBleConnectionLed(false);
            state = stIdle;

        case stDisabled:
            break;

        default:
            break;
    }
}


void
battery_statusDisable(void)
{
    RKH_ENTER_CRITICAL();

    bsp_setMotionLed(false);
    bsp_setBatteryLed(false);
    bsp_setBleConnectionLed(false);

    state = stDisabled;

    RKH_EXIT_CRITICAL();
}

void
battery_statusEnable(BleScanStatus ble)
{
    RKH_ENTER_CRITICAL();

    state = stIdle;
    currentBleScanStatus = ble;

    RKH_EXIT_CRITICAL();
}

/* ------------------------------ End of file ------------------------------ */
