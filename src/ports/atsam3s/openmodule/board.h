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

// Names of the Pins
    typedef enum PinName {

        // mbed DIP -> LPC equivalencies, according to mbed schematics
        PA0 = ARM_PA_0,
        PA1 = ARM_PA_1,
        PA2 = ARM_PA_2,
        PA3 = ARM_PA_3,
        PA30 = ARM_PA_30,
        PA29 = ARM_PA_29,
        PA28 = ARM_PA_28,
        PA27 = ARM_PA_27,
        PA4 = ARM_PA_4,
        PA5 = ARM_PA_5,
        PA6 = ARM_PA_6,
        PA7 = ARM_PA_7,
        PA8 = ARM_PA_8,
        PA9 = ARM_PA_9,
        PA10 = ARM_PA_10,
        PA11 = ARM_PA_11,
        PA12 = ARM_PA_12,
        PA26 = ARM_PA_26,
        PA25 = ARM_PA_25,
        PA24 = ARM_PA_24,
        PA13 = ARM_PA_13,
        PA14 = ARM_PA_14,
        PA15 = ARM_PA_15,
        PA16 = ARM_PA_16,

        PA20 = ARM_PA_20,
        PA23 = ARM_PA_23,
        PA22 = ARM_PA_22,
        PA19 = ARM_PA_19,
        PA21 = ARM_PA_21,
        PA18 = ARM_PA_18,
        PA17 = ARM_PA_17,
        
        AD7 = ARM_PB_3,
        AD6 = ARM_PB_2,
        AD5 = ARM_PB_1,
        AD4 = ARM_PB_0,

        PA31 = ARM_PA_31,

        // Extra pins
        LED1 = ARM_PA_24,
        LED2 = ARM_PA_13,
        LED3 = ARM_PA_14,
        LED4 = ARM_PA_15,

        SW1 = ARM_PA_27,
        SW2 = ARM_PA_28,
        SW3 = ARM_PA_29,
        SW4 = ARM_PA_30,

        //USBTX = ARM_P0_2,
        //USBRX = ARM_P0_3,

        } PinName;

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
