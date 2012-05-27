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

uint32_t i;
Pin_t leds[4];
Pin_t pin;

void count0(void) {
    Pin_Toggle(leds[0]);
}

void count1(void) {
    Pin_Toggle(leds[1]);
}

void count2(void) {
    Pin_Toggle(leds[2]);
}

void count3(void) {
    Pin_Toggle(leds[3]);
}

void count4(void) {
    Pin_Toggle(pin);
}

/* This example uses timer interrupts to toggle the leds,
 * and also toggles a pin as fast as possible. */
int main(void) {

    // Get all the leds
    leds[0] = Pin_Get(LED1);
    leds[1] = Pin_Get(LED2);
    leds[2] = Pin_Get(LED3);
    leds[3] = Pin_Get(LED4);
    pin = Pin_Get(P5);

    Pin_Output(leds[0]);
    Pin_Output(leds[1]);
    Pin_Output(leds[2]);
    Pin_Output(leds[3]);
    Pin_Output(pin);

    // Blink at different rates
    Scheduler_t s1 = Scheduler_Init(count0, 1000000, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 500000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 250000, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 125000, 1);

    // Blink at the same time
    /*
    Scheduler_t s1 = Scheduler_Init(count0, 500000, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 500000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 500000, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 500000, 1);
    */

    // Fast timer
    Scheduler_t s5 = Scheduler_Init(count4, 20, 1);

    while (1) {
        // Do nothing
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
