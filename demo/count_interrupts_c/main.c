/*
 * libmanyuc - Measure speed of interrupt handling in C
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

uint32_t i,j;
Pin_t debug;

// Interrupt counter, toggles debug pin when 100k interrupts happen.
void count(void) {
    i++;
    if (i >= 100000) {
        Pin_Toggle(debug);
        i = 0;
    }
}

/* This example counts the number of interrupts received on several pins, which
 * are toggled by the program in an infinite loop, toggling a certain pin after
 * 100k interrupts. */
int main(void) {

    debug = Pin_Init(P5, 1, Output);

    // This indexes indicate how many interrupts are configured
    // And how many are going to be activated in the program code.
    int start_config = 0;
    int config_ints = 16;
    int start_active = 4;
    int active_ints = 9;

    // Pins used for interrupts
    Pin_t ins[16];

    ins[0] = Pin_Init(ARM_P0_0, 1, Output);
    ins[1] = Pin_Init(ARM_P0_1, 1, Output);
    ins[2] = Pin_Init(ARM_P0_4, 1, Output);
    ins[3] = Pin_Init(ARM_P0_5, 1, Output);
    ins[4] = Pin_Init(ARM_P0_23, 1, Output);
    ins[5] = Pin_Init(ARM_P0_24, 1, Output);
    ins[6] = Pin_Init(ARM_P0_25, 1, Output);
    ins[7] = Pin_Init(ARM_P0_26, 1, Output);
    ins[8] = Pin_Init(ARM_P2_0, 1, Output);
    ins[9] = Pin_Init(ARM_P2_1, 1, Output);
    ins[10] = Pin_Init(ARM_P2_2, 1, Output);
    ins[11] = Pin_Init(ARM_P2_3, 1, Output);
    ins[12] = Pin_Init(ARM_P2_4, 1, Output);
    ins[13] = Pin_Init(ARM_P2_5, 1, Output);
    ins[14] = Pin_Init(ARM_P0_16, 1, Output);
    ins[15] = Pin_Init(ARM_P0_15, 1, Output);

    for (j = start_config; j < config_ints; j++) {
        Pin_Int_Attach(ins[j], count, IOIntFall);
    }

    i = 0;
    while (1) {
        for (j = start_active; j < active_ints; j++) {
            Pin_On(ins[j]);
            Pin_Off(ins[j]);
        }
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
