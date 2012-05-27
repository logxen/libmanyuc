/*
 * libmanyuc - Test arch io file
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

#include "port.h"
#include "board.h"

/*----------------------------------------------------------------------------
  Digital Input / Output
 *----------------------------------------------------------------------------*/

static __INLINE void _turn_on(uint32_t port, uint32_t mask) {
    GIO->PORT[port].IOPIN |= (mask);
}

static __INLINE void _turn_off(uint32_t port, uint32_t mask) {
    GIO->PORT[port].IOPIN &= ~(mask);
}

static __INLINE void _set_output(uint32_t port, uint32_t mask) {
    GIO->PORT[port].IODIR |= mask;
}

static __INLINE void _set_input(uint32_t port, uint32_t mask) {
    GIO->PORT[port].IODIR &= ~(mask);
}

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get(PinName pin_name) {
    Pin_t pin = { pin_name / 32, pin_name % 32, 1 << (pin_name % 32) };
    return pin;
}

// Switch Pin On
void Pin_On(Pin_t pin) {
    _turn_on(pin.port, pin.mask);
}

// Switch Pin Off
void Pin_Off(Pin_t pin) {
    _turn_off(pin.port, pin.mask);
}

// Set pin as output
void Pin_Output(Pin_t pin) {
    _set_output(pin.port, pin.mask);
}

// Set pin as input
void Pin_Input(Pin_t pin) {
    _set_input(pin.port, pin.mask);
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
    // Ignored right now.
}

// Read pin state
int Pin_Read(Pin_t pin) {
    return ((GIO->PORT[pin.port].IOPIN & pin.mask) ? 1 : 0);
}

/*----------------------------------------------------------------------------
  Bus Mode Digital Input / Output
 *----------------------------------------------------------------------------*/

PinBus_t vPinBus_Get(int npins, va_list pins) {

    int i;
    PinBus_t bus = { { {0, {0, 0}}, {0, {0, 0}}, {0, {0, 0}}, {0, {0, 0}}, {0, {0, 0}} } };
    for (i = 0; i < npins; i++) {
        uint32_t address = va_arg(pins, uint32_t);
        uint8_t number = address % 32;
        // Add the pin to the 32 pin mask
        bus.ports[address / 32].mask |= 1 << number;
        // And the pin to the 16 pin mask with 2 bits per pin.
        if (number < 16) {
            bus.ports[address / 32].half_mask[0] |= 3 << (number * 2);
        } else {
            bus.ports[address / 32].half_mask[1] |= 3 << ((number - 16) * 2);
        }
    }
    return bus;
}

// Apply a function to all the ports affected in this bus
__INLINE void _PinBus_Apply(PinBus_t bus, void function(uint32_t,
uint32_t)) {
    int port;
    for (port = 0; port < 5; port++) {
        if (bus.ports[port].mask) {
            function(port, bus.ports[port].mask);
        }
    }
}

// Switch PinBus On
void PinBus_On(PinBus_t bus) {
    _PinBus_Apply(bus, _turn_on);
}

// Switch PinBus Off
void PinBus_Off(PinBus_t bus) {
    _PinBus_Apply(bus, _turn_off);
}

// Set PinBus as Output
void PinBus_Output(PinBus_t bus) {
    _PinBus_Apply(bus, _set_output);
}

// Set PinBus as Input
void PinBus_Input(PinBus_t bus) {
    _PinBus_Apply(bus, _set_input);
}

// Set pin bus input mode
void PinBus_Mode(PinBus_t bus, PinMode mode) {
    // Ignored right now.
}
