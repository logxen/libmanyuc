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
        Pin_Init(LED1, 1, Output),
        Pin_Init(LED2, 1, Output),
        Pin_Init(LED3, 1, Output),
        Pin_Init(LED4, 1, Output)
    };
    int nleds = 4, i = 0;

    // Turn all leds on and then off,
    // with a delay of 0.2s among operations.
    // This goes on indefinitely
    while (1) {
        for (i = 0; i < nleds; i++) {
            Pin_On(leds[i]);
            Delay(0.2);
        }
        for (i = 0; i < nleds; i++) {
            Pin_Off(leds[i]);
            Delay(0.2);
        }
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
