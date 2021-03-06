/*
 * libmanyuc - Turn leds on in C++ example
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

/* This example turns the leds on and off, one by one. */

int main() {

    // Construct all the pins on the given LEDs.
    // When no parameter is given, they are
    // automatically set as Output.
    Pin leds[] = {
        Pin(LED1), Pin(LED2),
        Pin(LED3), Pin(LED4)
    };

    // Go through all the LEDs and turn them on and off.
    // The leds are on for only 0.2s each.
    while (1) {
        for (int i = 0; i < 4; i++) {
            leds[i] = 1;
            Delay(0.2);
            leds[i] = 0;
        }
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
