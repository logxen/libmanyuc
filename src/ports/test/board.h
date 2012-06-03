/*
 * libmanyuc - test PC arch specifications file
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

#ifndef TEST_PORTMACRO_H
#define TEST_PORTMACRO_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define __INLINE inline

    typedef struct
    {
        uint32_t IODIR;
        uint32_t IOPIN;
    } Port_IO_TypeDef;

    typedef struct
    {
        Port_IO_TypeDef PORT[5];
    } IO_TypeDef;

// Global variable
    extern IO_TypeDef *GIO;

// Names of the Pins
    enum PinName {

        // The UC pin names
        UC_P0_0 = 0, UC_P0_1, UC_P0_2, UC_P0_3,
        UC_P0_4, UC_P0_5, UC_P0_6, UC_P0_7, UC_P0_8, UC_P0_9,
        UC_P0_10, UC_P0_11, UC_P0_12, UC_P0_13, UC_P0_14, UC_P0_15,
        UC_P0_16, UC_P0_17, UC_P0_18, UC_P0_19, UC_P0_20, UC_P0_21,
        UC_P0_22, UC_P0_23, UC_P0_24, UC_P0_25, UC_P0_26, UC_P0_27,
        UC_P0_28, UC_P0_29, UC_P0_30, UC_P0_31, UC_P1_0, UC_P1_1,
        UC_P1_2, UC_P1_3, UC_P1_4, UC_P1_5, UC_P1_6, UC_P1_7,
        UC_P1_8, UC_P1_9, UC_P1_10, UC_P1_11, UC_P1_12, UC_P1_13,
        UC_P1_14, UC_P1_15, UC_P1_16, UC_P1_17, UC_P1_18, UC_P1_19,
        UC_P1_20, UC_P1_21, UC_P1_22, UC_P1_23, UC_P1_24, UC_P1_25,
        UC_P1_26, UC_P1_27, UC_P1_28, UC_P1_29, UC_P1_30, UC_P1_31,
        UC_P2_0, UC_P2_1, UC_P2_2, UC_P2_3, UC_P2_4, UC_P2_5,
        UC_P2_6, UC_P2_7, UC_P2_8, UC_P2_9, UC_P2_10, UC_P2_11,
        UC_P2_12, UC_P2_13, UC_P2_14, UC_P2_15, UC_P2_16, UC_P2_17,
        UC_P2_18, UC_P2_19, UC_P2_20, UC_P2_21, UC_P2_22, UC_P2_23,
        UC_P2_24, UC_P2_25, UC_P2_26, UC_P2_27, UC_P2_28, UC_P2_29,
        UC_P2_30, UC_P2_31, UC_P3_0, UC_P3_1, UC_P3_2, UC_P3_3,
        UC_P3_4, UC_P3_5, UC_P3_6, UC_P3_7, UC_P3_8, UC_P3_9,
        UC_P3_10, UC_P3_11, UC_P3_12, UC_P3_13, UC_P3_14, UC_P3_15,
        UC_P3_16, UC_P3_17, UC_P3_18, UC_P3_19, UC_P3_20, UC_P3_21,
        UC_P3_22, UC_P3_23, UC_P3_24, UC_P3_25, UC_P3_26, UC_P3_27,
        UC_P3_28, UC_P3_29, UC_P3_30, UC_P3_31, UC_P4_0, UC_P4_1,
        UC_P4_2, UC_P4_3, UC_P4_4, UC_P4_5, UC_P4_6, UC_P4_7,
        UC_P4_8, UC_P4_9, UC_P4_10, UC_P4_11, UC_P4_12, UC_P4_13,
        UC_P4_14, UC_P4_15, UC_P4_16, UC_P4_17, UC_P4_18, UC_P4_19,
        UC_P4_20, UC_P4_21, UC_P4_22, UC_P4_23, UC_P4_24, UC_P4_25,
        UC_P4_26, UC_P4_27, UC_P4_28, UC_P4_29, UC_P4_30, UC_P4_31,

        // outside DIP -> UC equivalencies.
        P5 = UC_P0_9,
        P6 = UC_P0_8,
        P7 = UC_P0_7,
        P8 = UC_P0_6,
        P9 = UC_P0_0,
        P10 = UC_P0_1,
        P11 = UC_P0_18,
        P12 = UC_P0_17,
        P13 = UC_P0_15,
        P14 = UC_P0_16,
        P15 = UC_P0_23,
        P16 = UC_P0_24,
        P17 = UC_P0_25,
        P18 = UC_P0_26,
        P19 = UC_P1_30,
        P20 = UC_P1_31,
        P21 = UC_P2_5,
        P22 = UC_P2_4,
        P23 = UC_P2_3,
        P24 = UC_P2_2,
        P25 = UC_P2_1,
        P26 = UC_P2_0,
        P27 = UC_P0_11,
        P28 = UC_P0_10,
        P29 = UC_P0_5,
        P30 = UC_P0_4,

        // Extra pins
        LED1 = UC_P1_18,
        LED2 = UC_P1_20,
        LED3 = UC_P1_21,
        LED4 = UC_P1_23,
        USBTX = UC_P0_2,
        USBRX = UC_P0_3,

        // Nicer names for existing pins
        // TODO

        // Not connected
        NC = (int)0xFFFFFFFF

    };
    typedef enum PinName PinName;

    typedef enum PinMode { Output = -1, PullUp = 0, Repeater = 1, PullNone = 2,
                           PullDown = 3, OpenDrain = 4
                         } PinMode;

    typedef enum IOIntMode {
        IOIntRise = 0, IOIntFall = 1,
    } IOIntMode;

// Pin structure to hold port and address
    struct _pin_t {
        uint16_t port;
        uint16_t address;
        uint32_t mask;
    };

// Port structure for buses
    typedef struct Port_t {
        uint32_t mask;
        uint32_t half_mask[2];
    } Port_t;

// Bus structure
    struct _pinBus_t {
        Port_t ports[5];
    };

    struct _i2c_t {
        uint8_t port;
        uint8_t address;
        uint8_t mode;
    };

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
