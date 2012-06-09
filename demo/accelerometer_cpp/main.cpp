/*
 * libmanyuc - Example of accelerometer use
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
#include "i2c_accelerometer.h"
#include <stdio.h>

/* This example shows the current angle by reading 
 * an accelorometer, and lighting up the leds*/



void show_angle(Pin* pins, float x) {

    pins[0] = 0;
    pins[1] = 0;
    pins[2] = 0;
    pins[3] = 0;

    int vel = (int)(x * 10);
    if (vel == 0) {
        pins[1] = 1;
        pins[2] = 1;
    } 
    if ((vel > -10) && (vel < -5)) pins[0] = 1;
    if ((vel > -6) && (vel < 0))   pins[1] = 1;
    if ((vel > 0) && (vel < 6))    pins[2] = 1;
    if ((vel > 5) && (vel < 10))   pins[3] = 1;

}

int main() {

    Pin leds[] = {
        Pin(LED1), Pin(LED2),
        Pin(LED3), Pin(LED4)
    };

    Accelerometer acer(2);
    float vect[3];

    while (1) {
        acer.get10BitVector(vect);
        show_angle(leds, vect[1]);
        Delay(0.3);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
