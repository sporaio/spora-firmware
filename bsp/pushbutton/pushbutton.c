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
 *  \file       pushbutton.c
 *  \brief      Simple Pushbutton debouncer and LONG/SHORT press detection
 *              statemachine
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
#include "rkh.h"
#include "bsp.h"
#include "spora.h"
#include "fsl_gpio.h"

/* ----------------------------- Local macros ------------------------------ */
#define pinRead()               GPIO_PinRead(PUSH_BUTTON_GPIO, \
                                             PUSH_BUTTON_GPIO_PIN)

/* ------------------------------- Constants ------------------------------- */
#define SHORT2LONG_BUTT_TIME    RKH_TIME_MS(3000)
#define DEBOUNCING_SAMPLES      7
#define PRESS_MASK              (1<<DEBOUNCING_SAMPLES)
#define RELEASE_MASK            (~(PRESS_MASK) && 0xFF)

typedef enum
{
    stReleased,
    stPress,
    stLongPress
}PushButtonState;

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static unsigned char filter, state, button;
static uint32_t tout;
static bool running = false;

#if defined(RKH_USE_TRC_SENDER)
static rui8_t pushbutton;
#endif

static RKH_STATIC_EVENT(e_pushbutton, evPushbuttonLongPress);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
pushbutton_init(void)
{
    port_pin_config_t sw_port_config = {kPORT_PullUp,
                                        kPORT_SlowSlewRate,
                                        kPORT_PassiveFilterDisable,
                                        kPORT_LowDriveStrength,
                                        kPORT_MuxAsGpio};

    gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0};

    PORT_SetPinConfig(PUSH_BUTTON_PORT,
                      PUSH_BUTTON_GPIO_PIN,
                      &sw_port_config);

    GPIO_PinInit(PUSH_BUTTON_GPIO,
                 PUSH_BUTTON_GPIO_PIN,
                 &sw_config);

    filter = 0;
    button = state = stReleased;
    running = true;
}

void
pushbutton_tick(void)
{
    if(!running)
        return;

    /* Debouncer filter */
    filter = (filter << 1) | pinRead(); 

    if(filter == RELEASE_MASK)
    {
        button = stReleased;
    }
    else if(filter == PRESS_MASK)
    {
        button = stPress;
    }

    /* Pushbutton state machine */
    switch(state)
    {
        case stReleased:
            if(button == stPress)
            {
                state = stPress;
                tout = SHORT2LONG_BUTT_TIME;
            }
            break;

        case stPress:
            if(button == stReleased)
            {
                RKH_SET_STATIC_EVENT(&e_pushbutton, evPushbuttonShortPress);
                RKH_SMA_POST_FIFO(spora, &e_pushbutton, &pushbutton);
                state = stReleased;
            }
            else if(tout && (--tout == 0))
            {
                RKH_SET_STATIC_EVENT(&e_pushbutton, evPushbuttonLongPress);
                RKH_SMA_POST_FIFO(spora, &e_pushbutton, &pushbutton);
                state = stLongPress;
            }
            break;

        case stLongPress:
            if(button == stReleased)
                state = stReleased;
            break;

        default:
            break;
    }
}

/* ------------------------------ End of file ------------------------------ */
