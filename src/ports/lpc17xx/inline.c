/*
 * libmanyuc - inline functions
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

// Static inline - Used by other functions
static inline uint32_t _get_half_port(struct _pin_t pin) {
    return (2 * pin.port) + pin.address / 16;
}

static inline uint32_t _get_half_mask(struct _pin_t pin) {
    return 2 * (pin.address % 16);
}

static inline void _turn_on(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIOSET = mask;
}

static inline void _turn_off(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIOCLR = mask;
}

static inline void _toggle(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIOPIN ^= mask;
}

static inline void _set_output(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIODIR |= mask;
}

static inline void _set_input(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIODIR &= ~(mask);
}

static inline void _set_open_drain(uint32_t port, uint32_t mask) {
    LPC_PINCON->PINMODE_OD[port] |= mask;
}

static inline void _set_normal_mode(uint32_t port, uint32_t mask) {
    LPC_PINCON->PINMODE_OD[port] &= ~(mask);
}

// Extern inline
static inline void Pin_On(struct _pin_t pin) {
    _turn_on(pin.port, pin.mask);
}

// Switch Pin Off
static inline void Pin_Off(struct _pin_t pin) {
    _turn_off(pin.port, pin.mask);
}

// Toggle Pin State
static inline void Pin_Toggle(struct _pin_t pin) {
    _toggle(pin.port, pin.mask);
}

// Read pin state
static inline int Pin_Read(struct _pin_t pin) {
    return ((LPC_GPIO[pin.port].FIOPIN & pin.mask) ? 1 : 0);
}

// Set pin as output
static inline void Pin_Output(struct _pin_t pin) {
    _set_output(pin.port, pin.mask);
}

// Set pin as input
static inline void Pin_Input(struct _pin_t pin) {
    _set_input(pin.port, pin.mask);
}

// Apply a function to all the ports affected in this bus
static inline void _PinBus_Apply(struct _pinBus_t bus, void function(uint32_t, uint32_t)) {
    int port;
    for (port = 0; port < MAX_PORTS; port++) {
        if (bus.ports[port].mask) {
            function(port, bus.ports[port].mask);
        }
    }
}

// Switch PinBus On
static inline void PinBus_On(struct _pinBus_t bus) {
    _PinBus_Apply(bus, _turn_on);
}

// Switch PinBus Off
static inline void PinBus_Off(struct _pinBus_t bus) {
    _PinBus_Apply(bus, _turn_off);
}

// Set PinBus as Output
static inline void PinBus_Output(struct _pinBus_t bus) {
    _PinBus_Apply(bus, _set_output);
}

// Set PinBus as Input
static inline void PinBus_Input(struct _pinBus_t bus) {
    _PinBus_Apply(bus, _set_input);
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
