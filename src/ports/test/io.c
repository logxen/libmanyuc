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
#include "portmacro.h"

/*----------------------------------------------------------------------------
  Digital Input / Output 
 *----------------------------------------------------------------------------*/

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get (PinName pin_name) {
	Pin_t pin = { pin_name / 32, pin_name % 32, 1 << (pin_name % 32) };
	return pin;
}

// Switch Pin On 
void Pin_On (Pin_t pin) {
    GIO->PORT[pin.port].IOPIN |= (pin.mask);
}

// Switch Pin Off 
void Pin_Off (Pin_t pin) {
    GIO->PORT[pin.port].IOPIN &= ~(pin.mask);
}

// Set pin as output 
void Pin_Output(Pin_t pin) {
    GIO->PORT[pin.port].IODIR |= pin.mask;
}

// Set pin as input 
void Pin_Input(Pin_t pin) {
    GIO->PORT[pin.port].IODIR &= ~(pin.mask);
}

// Set pin input mode
void Pin_Input_Mode(Pin_t pin, PinMode mode) {
	// Ignored right now.
}

// Read pin state 
int Pin_Read (Pin_t pin) {
    return ((GIO->PORT[pin.port].IOPIN & pin.mask) ? 1 : 0); 
}
