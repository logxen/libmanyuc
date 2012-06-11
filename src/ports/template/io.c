/*
 * libmanyuc - Template IO file
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

#include "io.h"
#include <stdarg.h>

// Convert the pin name to a pin struct. 
Pin_t Pin_Get(PinName pin_name) {
    Pin_t pin;
    return pin;
}

// Set pin input/output mode
void Pin_Mode(Pin_t pin, PinMode mode) {

}

// Construct a pin bus
PinBus_t vPinBus_Get(int npins, va_list pins) {
    PinBus_t bus;
    return bus;
}

// Set PinBus input/output mode
void PinBus_Mode(PinBus_t bus, PinMode mode) {
}

// Returns this arch's leds.
PinBus_t PinBus_Get_Notification() {
    return PinBus_Get(0);
}

// Interrupt handling


// Enable interrupts on this pin
void Pin_Int_Enable(struct _pin_t pin, IOIntMode mode) {

}

// Disable interrupts on this pin
void Pin_Int_Disable(struct _pin_t pin, IOIntMode mode) {

}

// Attach a function to a pin interrupt. Once this is done, enable the
// interrupt.
void Pin_Int_Attach(struct _pin_t pin, void(*function)(void), IOIntMode mode) {

}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
