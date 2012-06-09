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
    leds[0] = Pin_Init(LED1, 1, Output);
    leds[1] = Pin_Init(LED2, 1, Output);
    leds[2] = Pin_Init(LED3, 1, Output);
    leds[3] = Pin_Init(LED4, 1, Output);

    // Get other pins to toggle.
    pins[0] = Pin_Init(P5, 1, Output);
    pins[1] = Pin_Init(P6, 1, Output);
    pins[2] = Pin_Init(P7, 1, Output);
    pins[3] = Pin_Init(P8, 1, Output);
    pins[4] = Pin_Init(P9, 1, Output);
    pins[5] = Pin_Init(P10, 1, Output);
    pins[6] = Pin_Init(P11, 1, Output);
    pins[7] = Pin_Init(P12, 1, Output);
    pins[8] = Pin_Init(P13, 1, Output);
    pins[9] = Pin_Init(P14, 1, Output);
    pins[10] = Pin_Init(P15, 1, Output);
    pins[11] = Pin_Init(P16, 1, Output);
    pins[12] = Pin_Init(P17, 1, Output);
    pins[13] = Pin_Init(P18, 1, Output);
    pins[14] = Pin_Init(P19, 1, Output);
    pins[15] = Pin_Init(P20, 1, Output);

    // Many different schedulers, 
    // going as fast as possible
    Scheduler_t s;
    s = Scheduler_Init_us(toggle_pin_0, 20, 1);
    s = Scheduler_Init_us(toggle_pin_1, 20, 1);
    s = Scheduler_Init_us(toggle_pin_2, 20, 1);
    s = Scheduler_Init_us(toggle_pin_3, 20, 1);

    s = Scheduler_Init_us(toggle_pin_4, 20, 1);
    s = Scheduler_Init_us(toggle_pin_5, 20, 1);
    s = Scheduler_Init_us(toggle_pin_6, 20, 1);
    s = Scheduler_Init_us(toggle_pin_7, 20, 1);

    s = Scheduler_Init_us(toggle_pin_8, 25, 1);
    s = Scheduler_Init_us(toggle_pin_9, 25, 1);
    s = Scheduler_Init_us(toggle_pin_10, 25, 1);
    s = Scheduler_Init_us(toggle_pin_11, 25, 1);
    s = Scheduler_Init_us(toggle_pin_12, 25, 1);
    s = Scheduler_Init_us(toggle_pin_13, 25, 1);
    s = Scheduler_Init_us(toggle_pin_14, 25, 1);
    s = Scheduler_Init_us(toggle_pin_15, 25, 1);

    // Small pause to sync.
    Delay_ms(1);

    // Blink at different rates
    Scheduler_t s1 = Scheduler_Init(count0, 1, 1);
    Scheduler_t s2 = Scheduler_Init_us(count1, 500000, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 0.25, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 0.125, 1);

    // Blink at the same time
/*    Scheduler_t s1 = Scheduler_Init(count0, 0.5, 1);
    Scheduler_t s2 = Scheduler_Init(count1, 0.5, 1);
    Scheduler_t s3 = Scheduler_Init(count2, 0.5, 1);
    Scheduler_t s4 = Scheduler_Init(count3, 0.5, 1); */
    
    while (1) {
        // Do nothing
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
