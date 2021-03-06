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

static const uint8_t port_ids[] = { 11, 12, 13 };

// Static inline - Used by other functions
static inline void _turn_on(uint32_t port, uint32_t mask) {
    PIO[port].PIO_SODR = mask;
}

static inline void _turn_off(uint32_t port, uint32_t mask) {
    PIO[port].PIO_CODR = mask;
}

static inline void _toggle(uint32_t port, uint32_t mask) {
    if (PIO[port].PIO_ODSR & mask) _turn_off(port, mask);
    else _turn_on(port, mask);
}

static inline void _set_output(uint32_t port, uint32_t mask) {
    PIO[port].PIO_OER = mask;
}

static inline void _set_input(uint32_t port, uint32_t mask) {
    PIO[port].PIO_ODR = mask;
    //PIO[port].PIO_PER = mask;
    //PIO[port].PIO_IFDR = mask;
    // TODO: put in a different function
    PMC->PMC_PCER0 = ( 1 << port_ids[port]);
}

static __INLINE void _set_input_mode(uint32_t port, 
    uint32_t mask, uint8_t mode) {
    // Set input type (PullUp, PullDown, PullNone)
    if (mode == PullUp) {
        PIO[port].PIO_PUER = mask;
        PIO[port].PIO_PPDDR = mask;
    } else if (mode == PullDown) {
        PIO[port].PIO_PUDR = mask;
        PIO[port].PIO_PPDER = mask;
    } else if (mode == PullNone) {
        PIO[port].PIO_PUDR = mask;
        PIO[port].PIO_PPDDR = mask;
    } else if (mode == OpenDrain) {
        PIO[port].PIO_MDER = mask;
    } else if (mode == NormalMode) {
        PIO[port].PIO_MDDR = mask;
    } else {
        // Set pin primary / secondary / etc function.
        mode -= 8;

        if (mode & 0x01) {
            PIO[port].PIO_ABCDSR[0] |= mask;
        } else {
            PIO[port].PIO_ABCDSR[0] &= ~(mask);
        }

        if (mode & 0x02) {
            PIO[port].PIO_ABCDSR[1] |= mask;
        } else {
            PIO[port].PIO_ABCDSR[1] &= ~(mask);
        }

    }
}

// *************************
// external inline functions
// *************************
// Read pin state
static inline int Pin_Read(struct _pin_t pin) {
    return ((PIO[pin.port].PIO_PDSR & pin.mask) ? 1 : 0);
}

// Switch Pin On
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
