/*
 * libmanyuc - LPC io file
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
#include "portmacro.h"

// Internal helper functions
static __INLINE uint32_t _get_half_port(Pin_t pin) {
	return (2 * pin.port) + pin.address / 16;
}

static __INLINE uint32_t _get_half_mask(Pin_t pin) {
	return 2 * (pin.address % 16);
}

static __INLINE void _turn_on(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIOPIN |= (mask);
// TODO LPC_GPIO[port].FIOSET = mask;
}

static __INLINE void _turn_off(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIOPIN &= ~(mask);
// TODO LPC_GPIO[port].FIOCLR = mask;
}

static __INLINE void _set_output(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIODIR |= mask;
}

static __INLINE void _set_input(uint32_t port, uint32_t mask) {
    LPC_GPIO[port].FIODIR &= ~(mask);
}

static __INLINE void _set_open_drain(uint32_t port, uint32_t mask) {
	LPC_PINCON->PINMODE_OD[port] |= mask;
}

/*----------------------------------------------------------------------------
  Digital Input / Output 
 *----------------------------------------------------------------------------*/

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get (PinName pin_name) {
	uint32_t address = pin_name - LPC_GPIO_BASE;
	Pin_t pin = { address / 32, address % 32, 1 << (address % 32) };
	return pin;
}

// Switch Pin On 
__INLINE void Pin_On (Pin_t pin) {
	_turn_on(pin.port, pin.mask);
}

// Switch Pin Off 
__INLINE void Pin_Off (Pin_t pin) {
	_turn_off(pin.port, pin.mask);
}

// Read pin state 
__INLINE int Pin_Read (Pin_t pin) {
    return ((LPC_GPIO[pin.port].FIOPIN & pin.mask) ? 1 : 0); 
}

// Set pin as output 
__INLINE void Pin_Output(Pin_t pin) {
	_set_output(pin.port, pin.mask);
}

// Set pin as input 
__INLINE void Pin_Input(Pin_t pin) {
    _set_input(pin.port, pin.mask);
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
	uint32_t port = _get_half_port(pin);
	uint32_t shift = _get_half_mask(pin);

	// Set input type (PullUp, PullDown, PullNone)
    if (mode < 4) {
        LPC_PINCON->PINMODE[port] &= ~(3 << shift);
        LPC_PINCON->PINMODE[port] |= (mode << shift);
	// Set opendrain
    } else if (mode == 4) {
		_set_open_drain(pin.port, pin.mask);
	// Set pin primary / secondary / etc function.
	} else {
		mode -= 8;
		LPC_PINCON->PINSEL[port] &= ~(3 << shift);
		LPC_PINCON->PINSEL[port] |= (mode << shift);
	}
}

/*----------------------------------------------------------------------------
  Bus Mode Digital Input / Output 
 *----------------------------------------------------------------------------*/

#include <stdarg.h>
PinBus_t PinBus_Get(int npins, ...) {
	va_list pins;
	va_start (pins, npins);

	int i;
	PinBus_t bus = { { {0,{0,0}}, {0,{0,0}}, {0,{0,0}}, {0,{0,0}}, {0,{0,0}} } };
	for (i = 0; i < npins; i++) {
	    uint32_t address = va_arg(pins, uint32_t) - LPC_GPIO_BASE;
		uint8_t number = address % 32;
		// Add the pin to the 32 pin mask
		bus.ports[address / 32].mask |= 1 << number;
		// And the pin to the 16 pin mask with 2 bits per pin.
		if (number < 16) {
			bus.ports[address / 32].half_mask[0] |= 3 << (number*2);
		} else {
			bus.ports[address / 32].half_mask[1] |= 3 << ((number-16)*2);
		}
	}
	va_end(pins);
    return bus;
}

// Apply a function to all the ports affected in this bus
__INLINE void _PinBus_Apply (PinBus_t bus, void function (uint32_t, uint32_t) ) {
	int port;
	for (port = 0; port < 5; port++) {
		if (bus.ports[port].mask) {
			function(port, bus.ports[port].mask);
		}
	}
}

// Switch PinBus On 
void PinBus_On (PinBus_t bus) {
	_PinBus_Apply(bus, _turn_on);
}

// Switch PinBus Off 
void PinBus_Off (PinBus_t bus) {
	_PinBus_Apply(bus, _turn_off);
}

// Set PinBus as Output
void PinBus_Output (PinBus_t bus) {
	_PinBus_Apply(bus, _set_output);
}

// Set PinBus as Input 
void PinBus_Input (PinBus_t bus) {
	_PinBus_Apply(bus, _set_input);
}

void PinBus_Mode(PinBus_t bus, PinMode mode) {
// TODO: lock for concurrency
	if (mode == OpenDrain) {
		return _PinBus_Apply(bus, _set_open_drain);
	}

	int i;
	// Create a 32bit mask that repeats the mode 16 times
	uint32_t mode_mask = mode & 0x3;
	for (i = 2; i < 32; i *= 2) {
		mode_mask = (mode_mask << i) + mode_mask;
	}

	int port;
	for (port = 0; port < 5; port++) {
		for (i = 0; i < 2; i++) {

			uint32_t pin_mask = bus.ports[port].half_mask[i];
			if (!pin_mask) continue;

			uint32_t value = pin_mask & mode_mask;
			uint8_t half_port = 2*port+i;
		    if (mode < 4) {
        		LPC_PINCON->PINMODE[half_port] &= ~(pin_mask);
		        LPC_PINCON->PINMODE[half_port] |= value;
			} else {
				LPC_PINCON->PINSEL[half_port] &= ~(pin_mask);
				LPC_PINCON->PINSEL[half_port] |= value;
			}
		}
	}
}

