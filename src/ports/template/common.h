/*
 * libmanyuc - Template specifications file
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

#ifndef TEMPLATE_COMMON_H
#define TEMPLATE_COMMON_H

/* Macros and declarations needed for this port */
#ifdef __cplusplus
extern "C" {
#endif

// Typedefs
    typedef enum InternalPinName {
    } InternalPinName;

    typedef enum PinMode {
    } PinMode;

    typedef enum IOIntMode {
    } IOIntMode;

    typedef enum AnalogInMode {
    } AnalogInMode;

// **********
// Structures
// **********

// Pin structure to hold port and address
    struct _pin_t {
    };

// Port structure for buses
    typedef struct Port_t {
    } Port_t;

// Bus structure
    struct _pinBus_t {
    };

// Serial port structure to hold all port info
    struct _serial_t {
    };

// PWM structure
    struct _pwm_pin_t {
    };

// Scheduler structure
    struct _scheduler_t {
    };

// I2C structure
    struct _i2c_t {
    };

// AnalogIn structure
    struct _analog_in_t {
    };

#include "inline.c"

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
