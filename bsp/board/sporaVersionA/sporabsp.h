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
 *  \file       sporafrdm.h
 *  \brief      Board Support Package Spora on FRDMKL03 kit.
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

#ifndef __SPORABSP_H__
#define __SPORABSP_H__

/* ----------------------------- Include files ----------------------------- */
#include "clock_config.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#ifdef BOARD_NAME
#undef BOARD_NAME
#define BOARD_NAME "SPORA-VERSION_A"
#endif

/* ================================== GPIO ================================= */

/* MPU9250 */    
#ifndef EXT_WAKE_UP_GPIO
#define EXT_WAKE_UP_GPIO          GPIOB
#endif
#ifndef EXT_WAKE_UP_PORT
#define EXT_WAKE_UP_PORT          PORTB
#endif
#ifndef EXT_WAKE_UP_GPIO_PIN
#define EXT_WAKE_UP_GPIO_PIN      5U
#endif
#define EXT_WAKE_UP_IRQ           PORTB_IRQn
#define EXT_WAKE_UP_IRQ_Handler   PORTB_IRQHandler
#define EXT_WAKE_UP_NAME          "EXT_WAKE_UP"

/* Push button */    
#ifndef PUSH_BUTTON_GPIO
#define PUSH_BUTTON_GPIO          GPIOA
#endif
#ifndef PUSH_BUTTON_PORT
#define PUSH_BUTTON_PORT          PORTA
#endif
#ifndef PUSH_BUTTON_GPIO_PIN
#define PUSH_BUTTON_GPIO_PIN      9U
#endif
#define PUSH_BUTTON_IRQ           PORTA_IRQn
#define PUSH_BUTTON_IRQ_Handler   PORTA_IRQHandler
#define PUSH_BUTTON_NAME          "PUSH_BUTTON"

/* Led RGB */
#define LOGIC_LED_ON 0U
#define LOGIC_LED_OFF 1U
#ifndef LED_RED_GPIO
#define LED_RED_GPIO GPIOA
#endif
#define LED_RED_GPIO_PORT PORTA
#ifndef LED_RED_GPIO_PIN
#define LED_RED_GPIO_PIN 6U
#endif

#define LED_RED_INIT(output) \
    GPIO_PinWrite(LED_RED_GPIO, LED_RED_GPIO_PIN, output); \
    LED_RED_GPIO->PDDR |= (1U << LED_RED_GPIO_PIN) 
#define LED_RED_ON() \
    GPIO_PortClear(LED_RED_GPIO, 1U << LED_RED_GPIO_PIN) 
#define LED_RED_OFF() \
    GPIO_PortSet(LED_RED_GPIO, 1U << LED_RED_GPIO_PIN) 
#define LED_RED_TOGGLE() \
    GPIO_PortToggle(LED_RED_GPIO, 1U << LED_RED_GPIO_PIN) 

#ifndef LED_GREEN_GPIO
#define LED_GREEN_GPIO GPIOA
#endif
#define LED_GREEN_GPIO_PORT PORTA
#ifndef LED_GREEN_GPIO_PIN
#define LED_GREEN_GPIO_PIN 12U
#endif

#define LED_GREEN_INIT(output) \
    GPIO_PinWrite(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, output); \
    LED_GREEN_GPIO->PDDR |= (1U << LED_GREEN_GPIO_PIN) 
#define LED_GREEN_ON() \
    GPIO_PortClear(LED_GREEN_GPIO, 1U << LED_GREEN_GPIO_PIN) 
#define LED_GREEN_OFF() \
    GPIO_PortSet(LED_GREEN_GPIO, 1U << LED_GREEN_GPIO_PIN) 
#define LED_GREEN_TOGGLE() \
    GPIO_PortToggle(LED_GREEN_GPIO, 1U << LED_GREEN_GPIO_PIN) 

#ifndef LED_BLUE_GPIO
#define LED_BLUE_GPIO GPIOB
#endif
#define LED_BLUE_GPIO_PORT PORTB
#ifndef LED_BLUE_GPIO_PIN
#define LED_BLUE_GPIO_PIN 13U
#endif

#define LED_BLUE_INIT(output) \
    GPIO_PinWrite(LED_BLUE_GPIO, LED_BLUE_GPIO_PIN, output); \
    LED_BLUE_GPIO->PDDR |= (1U << LED_BLUE_GPIO_PIN) 
#define LED_BLUE_ON() \
    GPIO_PortClear(LED_BLUE_GPIO, 1U << LED_BLUE_GPIO_PIN)
#define LED_BLUE_OFF() \
    GPIO_PortSet(LED_BLUE_GPIO, 1U << LED_BLUE_GPIO_PIN) 
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(LED_BLUE_GPIO, 1U << LED_BLUE_GPIO_PIN) 

/* Murata ZYZ */
#ifndef BLE_RESET_GPIO
#define BLE_RESET_GPIO GPIOB
#endif
#define BLE_RESET_PORT PORTB
#ifndef BLE_RESET_GPIO_PIN
#define BLE_RESET_GPIO_PIN 2
#endif

#define BLE_RESET_INIT(output) \
    GPIO_PinWrite(BLE_RESET_GPIO, BLE_RESET_GPIO_PIN, output); \
    LED_BLUE_GPIO->PDDR |= (1U << BLE_RESET_GPIO_PIN) 
#define BLE_RESET_RELEASE() \
    GPIO_PortClear(BLE_RESET_GPIO, 1U << BLE_RESET_GPIO_PIN)
#define BLE_RESET_SET() \
    GPIO_PortSet(BLE_RESET_GPIO, 1U << BLE_RESET_GPIO_PIN) 

/* Battery */
#ifndef BATTERY_STATUS_GPIO
#define BATTERY_STATUS_GPIO          GPIOB
#endif
#ifndef BATTERY_STATUS_PORT
#define BATTERY_STATUS_PORT          PORTB
#endif
#ifndef BATTERY_STATUS_GPIO_PIN
#define BATTERY_STATUS_GPIO_PIN      1U
#endif
    
       
/* ================================= LPUART ================================ */
#define CODELESS_LPUART                 LPUART0
#define CODELESS_LPUART_CLKSRC          SYS_CLK
#define CODELESS_LPUART_CLK_FREQ        CLOCK_GetFreq(SYS_CLK)
#define CODELESS_LPUART_IRQn            LPUART0_IRQn
#define CODELESS_LPUART_IRQHandler      LPUART0_IRQHandler
#define CODELESS_LPUART_BAUDRATE        57600

#define BLE_LPUART_TX_PORT              PORTA
#define BLE_LPUART_TX_PIN               3U
#define BLE_LPUART_TX_MUXOPT            kPORT_MuxAlt4

#define BLE_LPUART_RX_PORT              PORTA
#define BLE_LPUART_RX_PIN               4U
#define BLE_LPUART_RX_MUXOPT            kPORT_MuxAlt4


/* ================================= GPIO ================================ */

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
