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
	Pin_t leds[] = { 
		Pin_Get(LED1), 
		Pin_Get(LED2), 
		Pin_Get(LED3), 
		Pin_Get(LED4) 
	};
	int nleds = 4, i = 0;

	// Set all pins as output
	for (i = 0; i < nleds; i++) {
		Pin_Output(leds[i]);
	}

	// Turn all leds on and then off, 
	// with a delay of 0.2s among operations.
    // This goes on indefinitely
    while(1) {
		for (i = 0; i < nleds; i++) {
			Pin_On(leds[i]);
        	wait(0.2);
		}
		for (i = 0; i < nleds; i++) {
			Pin_Off(leds[i]);
        	wait(0.2);
		}
    }
}
