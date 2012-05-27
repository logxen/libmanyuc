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
#include "i2c_accelerometer.h"

/* This example  */

Pin LA(LED1);
Pin LB(LED2);
Pin LC(LED3);
Pin LD(LED4);

void show_angle(float x) {

    LA = LB = LC = LD = 0;

    int vel = (int)(x*10);

    if ((vel > 0) && (vel < 6))    LC = 1;
    if ((vel > 5) && (vel < 10))   LD = 1;
    if ((vel > -6) && (vel < 0))   LB = 1;
    if ((vel > -10) && (vel < -5)) LA = 1;

}

int main() {

	Accelerometer acer;
	float vect[3];

    while(1) {
		acer.get10BitVector(vect);
		show_angle(vect[1]);
		wait(0.3);
    }
}
