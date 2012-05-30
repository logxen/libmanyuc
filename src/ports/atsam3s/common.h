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

#ifndef ATSAM3S_COMMON_H
#define ATSAM3S_COMMON_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include "SAM3S.h"


// Names of the Pins
    typedef enum InternalPinName {

        // The ARM pin names
        ARM_PA_0, ARM_PA_1, ARM_PA_2, ARM_PA_3, ARM_PA_4, ARM_PA_5,
        ARM_PA_6, ARM_PA_7, ARM_PA_8, ARM_PA_9, ARM_PA_10, ARM_PA_11,
        ARM_PA_12, ARM_PA_13, ARM_PA_14, ARM_PA_15, ARM_PA_16, ARM_PA_17,
        ARM_PA_18, ARM_PA_19, ARM_PA_20, ARM_PA_21, ARM_PA_22, ARM_PA_23,
        ARM_PA_24, ARM_PA_25, ARM_PA_26, ARM_PA_27, ARM_PA_28, ARM_PA_29,
        ARM_PA_30, ARM_PA_31, ARM_PB_0, ARM_PB_1, ARM_PB_2, ARM_PB_3,
        ARM_PB_4, ARM_PB_5, ARM_PB_6, ARM_PB_7, ARM_PB_8, ARM_PB_9,
        ARM_PB_10, ARM_PB_11, ARM_PB_12, ARM_PB_13, ARM_PB_14, ARM_PB_15,
        ARM_PB_16, ARM_PB_17, ARM_PB_18, ARM_PB_19, ARM_PB_20, ARM_PB_21,
        ARM_PB_22, ARM_PB_23, ARM_PB_24, ARM_PB_25, ARM_PB_26, ARM_PB_27,
        ARM_PB_28, ARM_PB_29, ARM_PB_30, ARM_PB_31, ARM_PC_0, ARM_PC_1,
        ARM_PC_2, ARM_PC_3, ARM_PC_4, ARM_PC_5, ARM_PC_6, ARM_PC_7,
        ARM_PC_8, ARM_PC_9, ARM_PC_10, ARM_PC_11, ARM_PC_12, ARM_PC_13,
        ARM_PC_14, ARM_PC_15, ARM_PC_16, ARM_PC_17, ARM_PC_18, ARM_PC_19,
        ARM_PC_20, ARM_PC_21, ARM_PC_22, ARM_PC_23, ARM_PC_24, ARM_PC_25,
        ARM_PC_26, ARM_PC_27, ARM_PC_28, ARM_PC_29, ARM_PC_30, ARM_PC_31, 

        // Internal equivalencies
        /*TX_0 = ARM_P0_2,
        RX_0 = ARM_P0_3,
        TX_1 = ARM_P0_10,
        RX_1 = ARM_P0_11,
        TX_2 = ARM_P0_15,
        RX_2 = ARM_P0_16,
        TX_3 = ARM_P0_0,
        RX_3 = ARM_P0_1,

        ADC0 = ARM_P0_23,
        ADC1 = ARM_P0_24,
        ADC2 = ARM_P0_25,
        ADC3 = ARM_P0_26,
        ADC4 = ARM_P1_30,
        ADC5 = ARM_P1_31,
        ADC6 = ARM_P0_3,
        ADC7 = ARM_P0_2,

        SDA0 = ARM_P0_27,
        SCL0 = ARM_P0_28,
        SDA1 = ARM_P0_19,
        SCL1 = ARM_P0_20,
        SDA2 = ARM_P0_10,
        SCL2 = ARM_P0_11,*/
    } InternalPinName;

    typedef enum PinMode {
        Output = -1,
        PullUp = 0, Repeater = 1, PullNone = 2, PullDown = 3,
        OpenDrain = 4, NormalMode = 5,
        // Pin Functions, start at 8
        PA = 8, PB, PC, PD,
    } PinMode;

    typedef enum IOIntMode {
        IOIntRise = 0, IOIntFall = 1,
    } IOIntMode;

// For serial ports
    typedef enum SerialPowerBit {
        PCUART0 = 3,
        PCUART1 = 4,
        PCUART2 = 24,
        PCUART3 = 25,
    } SerialPowerBit;

    typedef enum SerialIRQType {
        RX_INT = 0,
        TX_INT = 1,
    } SerialIRQType;

// **********
// Structures
// **********

// Pin structure to hold port and address
    struct _pin_t {
        uint8_t port;
        uint8_t address;
        uint32_t mask;
    };
// TODO: maybe the masks could be in code and use a macro to get them?

// Port structure for buses
    typedef struct Port_t {
        uint32_t mask;
    } Port_t;

// Bus structure
#define MAX_PORTS 4
    struct _pinBus_t {
        Port_t ports[MAX_PORTS];
    };

// Serial port structure to hold all port info
    struct _serial_t {
        struct _pin_t tx;
        struct _pin_t rx;
        Uart *uart;
        uint32_t number;
    };

// PWM structure
    struct _pwm_pin_t {
        uint32_t id;
    };

// Scheduler structure
    struct _scheduler_t {
        uint8_t timer_id;
        uint8_t mr_id;
    };

    struct _i2c_t {
        uint8_t port;
        uint8_t address;
        uint8_t mode;
    };

#include "inline.c"

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
