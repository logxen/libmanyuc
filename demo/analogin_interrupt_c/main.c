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
#include <stdio.h>
#include <stdlib.h>

/* This example reads two sensors, using the ADC3 and ADC4.
   To do that, the pins in P9 and P10 have to be turned on.
   The output read is sent through the serial port and the
   pins P20 and P30 are turned on or off according to the value. 
   
   This example shows how to read using interrupts instead of blocking
   the CPU. Interrupts can be used once or many times. When using the
   Read_All alternative, you can set the speed of the reading.
   */

uint32_t i = 0, j = 0;
AnalogIn_t in1, in2;
Serial_t port;
Pin_t light1, light2;
uint32_t value1, value2;

void count1(uint32_t value) {
    i++;
    value1 = value;
    if (i >= 10000) {
        Pin_Toggle(light1);
        i = 0;
    }
// Uncomment the next line when using read one instead of read all
//    AnalogIn_Read(in2, ADC_INTERRUPT);
}

void count2(uint32_t value) {
    j++;
    value2 = value;
    if (j >= 10000) {
        Pin_Toggle(light2);
        j = 0;
    }
// Uncomment the next line when using read one instead of read all
//    AnalogIn_Read(in1, ADC_INTERRUPT);
}


int main(void) {

#ifdef DEBUG
    Serial_t port = Serial_Init(0, 9600);
    Serial_Put_Bytes(port, "start\r\n", 7, BLOCKING);
    char cadena[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
#endif

    in1 = AnalogIn_Init(ADC4);
    in2 = AnalogIn_Init(ADC3);

    Pin_t sensor1 = Pin_Init(P9, 1, Output);
    Pin_t sensor2 = Pin_Init(P10, 1, Output);

    light1 = Pin_Init(P20, 1, Output);
    light2 = Pin_Init(P30, 1, Output);

    Pin_On(sensor1);
    Pin_On(sensor2);

    AnalogIn_Attach(in1, count1);
    AnalogIn_Attach(in2, count2);
    // Uncomment the next line when using read one instead of read all
//    AnalogIn_Read(in1, ADC_INTERRUPT);
    // Comment the next line when using read one instead of read all
    AnalogIn_Read_All(1);

    while (1) {
#ifdef DEBUG
        sprintf(cadena, "1: %d\r\n\0\0\0\0", value1);
        Serial_Put_Bytes(port, cadena, 9, BLOCKING);
        sprintf(cadena, "2: %d\r\n\r\n", value2);
        Serial_Put_Bytes(port, cadena, 11, BLOCKING);
#endif
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
