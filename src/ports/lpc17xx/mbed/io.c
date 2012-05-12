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
#include "board.h"

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get (PinName pin_name) {
	uint32_t address = pin_name - LPC_GPIO_BASE;
	Pin_t pin = { address / 32, address % 32, 1 << (address % 32) };
	return pin;
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

#include <stdarg.h>
PinBus_t vPinBus_Get(int npins, va_list pins) {
	int i;
	PinBus_t bus = { { {0,{0,0}}, {0,{0,0}}, {0,{0,0}}, } };

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
    return bus;
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
	for (port = 0; port < MAX_PORTS; port++) {
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

