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

/* This example counts the number of interrupts received on
 * pin 10, showing the number in binary using the leds. */

// Conting variable
uint32_t i;
// Leds used to show the result of the count
Bus_t leds;

void count(void) {
    i++;
    Bus_Write(leds, i);
}

int main(void) {

    // Creates a bus with the 4 leds
    leds = Bus_Get(4, LED4, LED3, LED2, LED1);
    Bus_Output(leds);

    Pin_t in = Pin_Init(P10, 1, Input, PullUp);
    Pin_Int_Attach(in, count, IOIntFall);

    int i = 0;
    // Show a binary combination of leds
    while (1) {
        // Do nothing
        Delay(1);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
