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

#ifndef MBED_PORTMACRO_H
#define MBED_PORTMACRO_H

/* Macros and declarations needed for this port */

#ifdef __cplusplus
extern "C" {
#endif

#include "LPC17xx.h"

// Names of the Pins
typedef enum PinName {

	// The ARM pin names
	ARM_P0_0 = LPC_GPIO_BASE, ARM_P0_1, ARM_P0_2, ARM_P0_3,
    ARM_P0_4, ARM_P0_5, ARM_P0_6, ARM_P0_7, ARM_P0_8, ARM_P0_9,
    ARM_P0_10, ARM_P0_11, ARM_P0_12, ARM_P0_13, ARM_P0_14, ARM_P0_15,
    ARM_P0_16, ARM_P0_17, ARM_P0_18, ARM_P0_19, ARM_P0_20, ARM_P0_21,
    ARM_P0_22, ARM_P0_23, ARM_P0_24, ARM_P0_25, ARM_P0_26, ARM_P0_27,
    ARM_P0_28, ARM_P0_29, ARM_P0_30, ARM_P0_31, ARM_P1_0, ARM_P1_1,
    ARM_P1_2, ARM_P1_3, ARM_P1_4, ARM_P1_5, ARM_P1_6, ARM_P1_7,
    ARM_P1_8, ARM_P1_9, ARM_P1_10, ARM_P1_11, ARM_P1_12, ARM_P1_13,
    ARM_P1_14, ARM_P1_15, ARM_P1_16, ARM_P1_17, ARM_P1_18, ARM_P1_19,
    ARM_P1_20, ARM_P1_21, ARM_P1_22, ARM_P1_23, ARM_P1_24, ARM_P1_25,
    ARM_P1_26, ARM_P1_27, ARM_P1_28, ARM_P1_29, ARM_P1_30, ARM_P1_31,
    ARM_P2_0, ARM_P2_1, ARM_P2_2, ARM_P2_3, ARM_P2_4, ARM_P2_5,
    ARM_P2_6, ARM_P2_7, ARM_P2_8, ARM_P2_9, ARM_P2_10, ARM_P2_11,
    ARM_P2_12, ARM_P2_13, ARM_P2_14, ARM_P2_15, ARM_P2_16, ARM_P2_17,
    ARM_P2_18, ARM_P2_19, ARM_P2_20, ARM_P2_21, ARM_P2_22, ARM_P2_23,
    ARM_P2_24, ARM_P2_25, ARM_P2_26, ARM_P2_27, ARM_P2_28, ARM_P2_29,
    ARM_P2_30, ARM_P2_31, ARM_P3_0, ARM_P3_1, ARM_P3_2, ARM_P3_3,
    ARM_P3_4, ARM_P3_5, ARM_P3_6, ARM_P3_7, ARM_P3_8, ARM_P3_9,
    ARM_P3_10, ARM_P3_11, ARM_P3_12, ARM_P3_13, ARM_P3_14, ARM_P3_15,
    ARM_P3_16, ARM_P3_17, ARM_P3_18, ARM_P3_19, ARM_P3_20, ARM_P3_21,
    ARM_P3_22, ARM_P3_23, ARM_P3_24, ARM_P3_25, ARM_P3_26, ARM_P3_27,
    ARM_P3_28, ARM_P3_29, ARM_P3_30, ARM_P3_31, ARM_P4_0, ARM_P4_1,
    ARM_P4_2, ARM_P4_3, ARM_P4_4, ARM_P4_5, ARM_P4_6, ARM_P4_7,
    ARM_P4_8, ARM_P4_9, ARM_P4_10, ARM_P4_11, ARM_P4_12, ARM_P4_13,
    ARM_P4_14, ARM_P4_15, ARM_P4_16, ARM_P4_17, ARM_P4_18, ARM_P4_19,
    ARM_P4_20, ARM_P4_21, ARM_P4_22, ARM_P4_23, ARM_P4_24, ARM_P4_25,
    ARM_P4_26, ARM_P4_27, ARM_P4_28, ARM_P4_29, ARM_P4_30, ARM_P4_31,

	// Internal equivalencies
	TX_0 = ARM_P0_2,
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

	// Nicer names for existing pins
	// TODO

    // Not connected
    NC = (int)0xFFFFFFFF

} PinName;

typedef enum PinMode { 
	Output = -1, 
	PullUp = 0, Repeater = 1, PullNone = 2, PullDown = 3, 
	OpenDrain = 4, NormalMode = 5,
	// Pin Functions, start at 8
	Primary = 8, Alt1, Alt2, Alt3, 
} PinMode;

typedef enum IOIntMode {
	IOIntRise = 0, IOIntFall = 1,
} IOIntMode;

// For serial ports
typedef enum SerialPortMode {
	S0_Mode = Alt1, 
	S1_Mode = Alt1, 
	S2_Mode = Alt1,
	S3_Mode = Alt2 
} SerialPortMode;

typedef enum UARTNumber {
    UART_0 = LPC_UART0_BASE, 
    UART_1 = LPC_UART1_BASE,
    UART_2 = LPC_UART2_BASE,
    UART_3 = LPC_UART3_BASE
} UARTNumber;

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
    uint32_t half_mask[2];
} Port_t;

// Bus structure
#define MAX_PORTS 3
struct _pinBus_t {
    Port_t ports[MAX_PORTS];
};

// Serial port structure to hold all port info
struct _serial_t {
	struct _pin_t tx;
	struct _pin_t rx;
	LPC_UART_TypeDef *uart;
	uint32_t number;
};

// PWM structure
struct _pwm_pin_t {
	    uint32_t id;
};


#include "inline.c"

#ifdef __cplusplus
}
#endif

#endif
