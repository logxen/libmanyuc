/*
 * libmanyuc - Example of using the serial port
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

/*
 This example repeats all the characters received from the serial port,
 through the serial port.  It also shows the lower half of the byte
 received using the leds.
*/

int main(void) {

    Pin_t leds[] = { 
        Pin_Init(LED4, 1, Output), 
        Pin_Init(LED3, 1, Output),
        Pin_Init(LED2, 1, Output), 
        Pin_Init(LED1, 1, Output)
    };
    int nleds = 4, i = 0;

    Serial_t port = Serial_Init(0, 9600);

    Pin_All_On(leds, nleds);
    Serial_Put_Bytes(port, BLOCKING, "Hola que tal, como te va 123456789 123456789\r\n", 46);

    FILE * f = Serial_Get_File(port);
    fprintf(f,"File pointer: %p\r\n", f);

    uint8_t buffer[1];
    while (1) {
        Serial_Get_Bytes(port, BLOCKING, buffer, 1);
        Pin_Show_Byte(leds, nleds, buffer[0]);
        Serial_Put_Bytes(port, BLOCKING, buffer, 1);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
