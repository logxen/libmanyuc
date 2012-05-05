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
static __INLINE uint32_t get_half_port(Pin_t pin) {
	return (2 * pin.port) + pin.address / 16;
}

static __INLINE uint32_t get_half_mask(Pin_t pin) {
	return 2 * (pin.address % 16);
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
    LPC_GPIO[pin.port].FIOPIN |= (pin.mask);
}

// Switch Pin Off 
__INLINE void Pin_Off (Pin_t pin) {
    LPC_GPIO[pin.port].FIOPIN &= ~(pin.mask);
}

// Read pin state 
__INLINE int Pin_Read (Pin_t pin) {
    return ((LPC_GPIO[pin.port].FIOPIN & pin.mask) ? 1 : 0); 
}

// Set pin as output 
__INLINE void Pin_Output(Pin_t pin) {
    LPC_GPIO[pin.port].FIODIR |= pin.mask;
}

// Set pin as input 
__INLINE void Pin_Input(Pin_t pin) {
    LPC_GPIO[pin.port].FIODIR &= ~(pin.mask);
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
	uint32_t port = get_half_port(pin);
	uint32_t shift = get_half_mask(pin);

	// Set input type (PullUp, PullDown, PullNone)
    if (mode < 4) {
        LPC_PINCON->PINMODE[port] &= ~(3 << shift);
        LPC_PINCON->PINMODE[port] |= (mode << shift);
	// Set opendrain
    } else if (mode == 4) {
		LPC_PINCON->PINMODE_OD[pin.port] |= pin.mask;
	// Set pin primary / secondary / etc function.
	} else {
		mode -= 8;
		LPC_PINCON->PINSEL[port] &= ~(3 << shift);
		LPC_PINCON->PINSEL[port] |= (mode << shift);
	}
}

