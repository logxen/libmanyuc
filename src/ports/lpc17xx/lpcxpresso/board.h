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

#ifndef LPCXPRESSO_BOARD_H
#define LPCXPRESSO_BOARD_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

    // Names of the Pins
    typedef enum PinName {

        // LPCXPresso pinout
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
        P21 = ARM_P0_2,
        P22 = ARM_P0_3,
        P23 = ARM_P0_21,
        P24 = ARM_P0_22,
        P25 = ARM_P0_27,
        P26 = ARM_P0_28,
        P27 = ARM_P2_13,
        P38 = ARM_P0_4,
        P39 = ARM_P0_5,
        P40 = ARM_P0_10,
        P41 = ARM_P0_11,
        P42 = ARM_P2_0,
        P43 = ARM_P2_1,
        P44 = ARM_P2_2,
        P45 = ARM_P2_3,
        P46 = ARM_P2_4,
        P47 = ARM_P2_5,
        P48 = ARM_P2_6,
        P49 = ARM_P2_7,
        P50 = ARM_P2_8,
        P51 = ARM_P2_10,
        P52 = ARM_P2_11,
        P53 = ARM_P2_12,

        // Extra pins
        LED1 = ARM_P0_22,
        LED2 = LED1,
        LED3 = LED1,
        LED4 = LED1,
        USBTX = ARM_P0_2,
        USBRX = ARM_P0_3,

        PAD1 = ARM_P1_18,
        PAD2 = ARM_P1_19,
        PAD3 = ARM_P1_20,
        PAD4 = ARM_P1_21,
        PAD5 = ARM_P1_22,
        PAD6 = ARM_P1_23,
        PAD7 = ARM_P1_24,
        PAD8 = ARM_P1_25,
        PAD9 = ARM_P1_26,
        PAD10 = ARM_P1_27,
        PAD11 = ARM_P1_28,
        PAD12 = ARM_P1_29,
        PAD13 = ARM_P3_25,
        PAD14 = ARM_P3_26,
        PAD15 = ARM_P4_28,
        PAD16 = ARM_P4_29,
        PAD17 = ARM_P0_19,
        PAD18 = ARM_P0_20,
        PAD19 = ARM_P2_9,

        } PinName;

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
