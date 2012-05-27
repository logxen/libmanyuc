/*
 * libmanyuc - Controll a servo motor in C example
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

/* This example makes a servo motor connected to pin 22,
 * turn left and then right */

// These values may change for a different servo motor
const float period_ms = 20;      // Period for the PWM
const float change_rate = 0.001; // Amount of variation in the duty cycle
const float stop_left = 0.10;    // Maximum value for the duty cycle
const float stop_right = 0.05;   // Minimum value for the duty cycle
const float pause_ms = 65;       // Pause between changes of the duty cycle.

float turn_left(Pin_t servo, float duty) {
    while (duty < stop_left) {
        PWMPin_Set_Duty_Cycle(servo, duty);
        duty += change_rate;
        wait_ms(pause_ms);
    }
    return duty;
}

float turn_right(Pin_t servo, float duty) {
    while (duty > stop_right) {
        PWMPin_Set_Duty_Cycle(servo, duty);
        duty -= change_rate;
        wait_ms(pause_ms);
    }
    return duty;
}

int main(void) {

    PWMPin_t servo = PWMPin_Get(P22);

    // Set the period for the PWM
    PWMPin_Set_Period_ms(servo, period_ms);

    // Infinitely turn left and then right.
    float duty = stop_right;
    while (1) {
        duty = turn_left(servo, duty);
        duty = turn_right(servo, duty);
    }
}
