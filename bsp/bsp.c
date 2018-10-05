/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       trace_io.c
 *  \brief      Socket COM Port support for DemoQE128-S08
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "fsl_lpuart.h"
#include "i2c.h"
#include "pin_mux.h"
#include "mpu9250.h"
#include "pushbutton.h"
#include "battery.h"
#include "bsp.h"
#include "blemgr.h"
#include "codeless.h"
#include "rkh.h"
#include "ssp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define TIME_SEC_COUNTER_RELOAD	RKH_TIME_MS(1000)
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static uint8_t tickCounter = TIME_SEC_COUNTER_RELOAD;
static uint32_t sleepCount;
static uint32_t timeSecCounter = 0;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
void CODELESS_LPUART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(CODELESS_LPUART))
    {
        data = LPUART_ReadByte(CODELESS_LPUART);
        ssp_doSearch(data);
    }
    /* Add for ARM errata 838869, affects Cortex-M4,
     * Cortex-M4F Store immediate overlapping exception return operation
     * might vector to incorrect interrupt
     */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void
SysTick_Handler(void)
{
	RKH_TIM_TICK(0);
    pushbutton_tick();
    mpu9250_sampler();
    battery_sampler();
    
    if(tickCounter && --tickCounter == 0)
    {
        tickCounter = TIME_SEC_COUNTER_RELOAD;
        ++timeSecCounter;
    }

    if(sleepCount)
        --sleepCount;
}

/* ---------------------------- Global functions --------------------------- */
void
bsp_init(void)
{
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 1};

    BOARD_InitPins();
    BOARD_BootClockRUN();

    SysTick_Config(SystemCoreClock/RKH_CFG_FWK_TICK_RATE_HZ);
    NVIC_SetPriority (SysTick_IRQn, RKH_PORT_IRQ_PRIO);

    I2C_releaseBus();
    BOARD_I2C_ConfigurePins();

    GPIO_PinInit(LED_RED_GPIO, LED_RED_GPIO_PIN, &led_config);
    GPIO_PinInit(LED_BLUE_GPIO, LED_BLUE_GPIO_PIN, &led_config);
    GPIO_PinInit(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, &led_config);
#ifdef MURATA_CODELESS_ON_ROM
    GPIO_PinInit(BLE_RESET_GPIO, BLE_RESET_GPIO_PIN, &led_config);

    BLE_RESET_SET();
#endif

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(blinky);
    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    RKH_ENA_INTERRUPT();
}

void
bsp_uartInit(void)
{
    lpuart_config_t config;

    CLOCK_SetLpuart0Clock(0x1U);
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kLPUART_ParityDisabled;
     * config.stopBitCount = kLPUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    LPUART_GetDefaultConfig(&config);

    config.baudRate_Bps = CODELESS_LPUART_BAUDRATE;
    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(CODELESS_LPUART, &config, CODELESS_LPUART_CLK_FREQ);    

    /* Enable RX interrupt. */
    LPUART_EnableInterrupts(CODELESS_LPUART, 
                            kLPUART_RxDataRegFullInterruptEnable);
    EnableIRQ(CODELESS_LPUART_IRQn);
}

void
bsp_sleep(uint16_t mdelay)
{
    RKH_ENTER_CRITICAL();
    sleepCount = mdelay;
    RKH_EXIT_CRITICAL();

    while(sleepCount);
}

void
bsp_uartPutstring(const char *s)
{
    LPUART_WriteBlocking(CODELESS_LPUART, (const uint8_t *)s, strlen(s));
}

void
bsp_uartPutchar(unsigned char c)
{
    LPUART_WriteBlocking(CODELESS_LPUART, &c, 1);
}

void
bsp_bleReset(bool state)
{
#ifdef MURATA_CODELESS_ON_ROM
	state == true ? BLE_RESET_SET() : BLE_RESET_RELEASE();
#endif
}

void
bsp_setBleConnectionLed(bool state)
{
	state == true ? LED_BLUE_ON() : LED_BLUE_OFF();
}

void
bsp_setMotionLed(bool state)
{
	state == true ? LED_RED_ON() : LED_RED_OFF();
}

void
bsp_toggleMotionLed(void)
{
	LED_RED_TOGGLE();
}

void
bsp_setBatteryLed(bool state)
{
	state == true ? LED_GREEN_ON() : LED_GREEN_OFF();
}

uint32_t
bsp_getTimeSec(void)
{
    return timeSecCounter;
}

/* ------------------------------ End of file ------------------------------ */
