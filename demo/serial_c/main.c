/*
 * libmanyuc - Example of using the serial port
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

void turn_on_all_leds(Pin_t* leds, int n) {
    int i;
    for (i = 0; i < n; i++) {
        Pin_On(leds[i]);
    }	
}

void turn_off_all_leds(Pin_t* leds, int n) {
    int i;
    for (i = 0; i < n; i++) {
        Pin_Off(leds[i]);
    }	
}

/*
 This example repeats all the characters received from the serial port,
 through the serial port.  It also shows the lower half of the byte
 received using the leds.
*/

int main(void) {

    Pin_t leds[] = { Pin_Get(LED1), Pin_Get(LED2),
        Pin_Get(LED3), Pin_Get(LED4) };

    int i;
    for (i = 0; i < 4; i++) {
        Pin_Output(leds[i]);
    }	

	Serial_t port = Serial_Get(0);
	Serial_Init(port, 9600);

	turn_on_all_leds(leds, 4);
    while(1) {
       	uint8_t byte = Serial_Get_Byte(port);
		int i;
		for (i = 0; i < 4; i++) {
			if (byte & (1 << i)) 
				Pin_On(leds[i]);
			else
				Pin_Off(leds[i]);
		}
		Serial_Put_Byte(port, byte);
    }
}
