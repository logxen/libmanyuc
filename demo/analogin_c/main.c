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

void number_to_char(uint32_t number, char *string) {

    int i;
    for (i = 0; i < 8; i++) {

        char letter = number % 16 + '0';
        if (letter > '9') letter = number % 16 - 10 + 'A';
        string[7-i] = letter;
        number = number / 16;
    }
}

/* This example reads two sensors, using the ADC3 and ADC4,
   to do that, the pins in P9 and P10 have to be turned on.
   The output read is sent through the serial port and the
   pins P20 and P30 are turned on or off according to the value. */
int main(void) {

    Serial_t port = Serial_Get(0);
    Serial_Init(port, 9600);

    char cadena[10];
    uint32_t p = AnalogIn_Get(ADC3);
    uint32_t q = AnalogIn_Get(ADC4);

    Pin_t sensor1 = Pin_Get(P9);
    Pin_t sensor2 = Pin_Get(P10);

    Pin_t light1 = Pin_Get(P20);
    Pin_t light2 = Pin_Get(P30);

    Pin_Output(sensor1);
    Pin_Output(sensor2);
    Pin_Output(light1);
    Pin_Output(light2);

    Pin_On(sensor1);
    Pin_On(sensor2);

    while (1) {
        uint16_t s1 = AnalogIn_Read(p);

        // Send the value through the serial port
        /*      snprintf(cadena, 10, "%d\r\n", s1);
                Serial_Put_Bytes(port, cadena, 6, BLOCKING);*/

        // Turn light on
        if (s1 > 2000) {
            Pin_On(light1);
        } else {
            Pin_Off(light1);
        }

        uint16_t s2 = AnalogIn_Read(q);

        /*      snprintf(cadena, 10, "%d\r\n", s2);
                Serial_Put_Bytes(port, cadena, 6, BLOCKING);*/

        if (s2 > 2000) {
            Pin_On(light2);
        } else {
            Pin_Off(light2);
        }
        wait(1);
    }
}
