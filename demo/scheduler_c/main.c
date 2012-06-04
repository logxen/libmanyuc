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

/* This example uses timer interrupts to toggle the leds,
 * and some of the pins as fast as possible. */

#include "libmanyuc.h"

uint32_t i;
Pin_t leds[4];
Pin_t pins[16];

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

void toggle_pin_0(void) { Pin_Toggle(pins[0]); }
void toggle_pin_1(void) { Pin_Toggle(pins[1]); }
void toggle_pin_2(void) { Pin_Toggle(pins[2]); }
void toggle_pin_3(void) { Pin_Toggle(pins[3]); }
void toggle_pin_4(void) { Pin_Toggle(pins[4]); }
void toggle_pin_5(void) { Pin_Toggle(pins[5]); }
void toggle_pin_6(void) { Pin_Toggle(pins[6]); }
void toggle_pin_7(void) { Pin_Toggle(pins[7]); }
void toggle_pin_8(void) { Pin_Toggle(pins[8]); }
void toggle_pin_9(void) { Pin_Toggle(pins[9]); }
void toggle_pin_10(void) { Pin_Toggle(pins[10]); }
void toggle_pin_11(void) { Pin_Toggle(pins[11]); }
void toggle_pin_12(void) { Pin_Toggle(pins[12]); }
void toggle_pin_13(void) { Pin_Toggle(pins[13]); }
void toggle_pin_14(void) { Pin_Toggle(pins[14]); }
void toggle_pin_15(void) { Pin_Toggle(pins[15]); }

int main(void) {

    // Get all the leds
    leds[0] = Pin_Get(LED1);
    leds[1] = Pin_Get(LED2);
    leds[2] = Pin_Get(LED3);
    leds[3] = Pin_Get(LED4);

    pins[0] = Pin_Get(P5);
    pins[1] = Pin_Get(P6);
    pins[2] = Pin_Get(P7);
    pins[3] = Pin_Get(P8);
    pins[4] = Pin_Get(P9);
    pins[5] = Pin_Get(P10);
    pins[6] = Pin_Get(P11);
    pins[7] = Pin_Get(P12);
    pins[8] = Pin_Get(P13);
    pins[9] = Pin_Get(P14);
    pins[10] = Pin_Get(P15);
    pins[11] = Pin_Get(P16);
    pins[12] = Pin_Get(P17);
    pins[13] = Pin_Get(P18);
    pins[14] = Pin_Get(P19);
    pins[15] = Pin_Get(P20);

    uint32_t i;
    for (i = 0; i < 4; i++) {
        Pin_Output(leds[i]);
    }
    for (i = 0; i < 16; i++) {
        Pin_Output(pins[i]);
    }

    // Blink at different rates

    Scheduler_t s;
    s = Scheduler_Init(toggle_pin_0, 5, 1);
    s = Scheduler_Init(toggle_pin_1, 5, 1);
    s = Scheduler_Init(toggle_pin_2, 5, 1);
    s = Scheduler_Init(toggle_pin_3, 5, 1);
/*
    Scheduler_t s1 = Scheduler_Init(count0, 1000000, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 500000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 250000, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 125000, 1);

    s = Scheduler_Init(toggle_pin_4, 500, 1);
    s = Scheduler_Init(toggle_pin_5, 600, 1);
    s = Scheduler_Init(toggle_pin_6, 700, 1);

    s = Scheduler_Init(toggle_pin_7, 800, 1);
    s = Scheduler_Init(toggle_pin_8, 900, 1);
    s = Scheduler_Init(toggle_pin_9, 200, 1);

    s = Scheduler_Init(toggle_pin_10, 100, 1);
    s = Scheduler_Init(toggle_pin_11, 200, 1);
    s = Scheduler_Init(toggle_pin_12, 300, 1);

    s = Scheduler_Init(toggle_pin_13, 100, 1);
    s = Scheduler_Init(toggle_pin_14, 200, 1);
    s = Scheduler_Init(toggle_pin_15, 10, 1);
*/


/*    Scheduler_t s1 = Scheduler_Init(count0, 500000, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 250000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 125000, 1);
    Scheduler_t s4 = Scheduler_Init(count3,  75000, 1);*/

    // Blink at the same time
    
/*    Scheduler_t s1 = Scheduler_Init(count0, 500000, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 500000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 500000, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 500000, 1);*/
    
    // Fast timer
    //wait(0.01);
/*    Scheduler_t s5 = Scheduler_Init(toggle_pin_0, 3, 1);
    Scheduler_t s6 = Scheduler_Init(toggle_pin_1, 3, 1);*/

    while (1) {
        // Do nothing
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
