/*
 * libmanyuc - LPC / mbed specifications file
 * Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef MBED_BOARD_H
#define MBED_BOARD_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define LED_ON 1
#define LED_OFF 0
#define SW_ON 0
#define SW_OFF 1


// Names of the Pins
    typedef enum PinName {

        // mbed DIP -> LPC equivalencies, according to mbed schematics
        P5 = ARM_P0_9,
        P6 = ARM_P0_8,
        P7 = ARM_P0_7,
        P8 = ARM_P0_6,
        P9 = ARM_P0_0,
        P10 = ARM_P0_1,
        P11 = ARM_P0_18,
        P12 = ARM_P0_17,
        P13 = ARM_P0_15,
        P14 = ARM_P0_16,
        P15 = ARM_P0_23,
        P16 = ARM_P0_24,
        P17 = ARM_P0_25,
        P18 = ARM_P0_26,
        P19 = ARM_P1_30,
        P20 = ARM_P1_31,
        P21 = ARM_P2_5,
        P22 = ARM_P2_4,
        P23 = ARM_P2_3,
        P24 = ARM_P2_2,
        P25 = ARM_P2_1,
        P26 = ARM_P2_0,
        P27 = ARM_P0_11,
        P28 = ARM_P0_10,
        P29 = ARM_P0_5,
        P30 = ARM_P0_4,

        // Extra pins
        LED1 = ARM_P1_18,
        LED2 = ARM_P1_20,
        LED3 = ARM_P1_21,
        LED4 = ARM_P1_23,
        USBTX = ARM_P0_2,
        USBRX = ARM_P0_3,

        } PinName;

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
