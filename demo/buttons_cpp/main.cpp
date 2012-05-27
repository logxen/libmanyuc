/*
 * libmanyuc - read buttons example
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

/* This example turns the first and second leds on, when buttons located
   in P20 and P19 are pressed.  Buttons are in PullUp mode, return 0 when
   pressed. */

int main() {

    Pin leds[] = {
        Pin(LED1), Pin(LED2),
        Pin(LED3), Pin(LED4)
    };

    Pin buttons[] = { Pin(P20, PullUp), Pin(P19, PullUp) };

    while (1) {
        for (int i = 0; i < 2; i++) {
            if (buttons[i] == 0) {
                leds[i] = 1;
            } else {
                leds[i] = 0;
            }
        }
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
