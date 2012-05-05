/*
 * libmanyuc - Turn leds on in C example
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

#include "libmanyuc.h"

/* This example turns all 4 leds on and then off */
int main(void) {

	// Access 4 leds predefined as LED1, LED2, LED3, LED4
	int nleds = 4, i = 0;
	PinBus_t leds = PinBus_Get (nleds, LED1, LED2, LED3, LED4);

	// Set all pins as output
	PinBus_Output(leds);

	// Turn all leds on and then off,
	// Waiting half a second in the middle 
    while(1) {
		PinBus_On(leds);
        wait(0.5);
		PinBus_Off(leds);
        wait(0.5);
    }
}
