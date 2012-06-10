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
 This example demonstrates the different ways of sending strings
 through the serial port: blocking, non-blocking, background, 
 using fprintf.

 Finally, the main loop repeats all the characters received from the
 serial port, through the serial port.  It also shows the lower half
 of the byte received using the leds.
*/

int main(void) {

    Pin_t leds[] = { 
        Pin_Init(LED4, 1, Output), 
        Pin_Init(LED3, 1, Output),
        Pin_Init(LED2, 1, Output), 
        Pin_Init(LED1, 1, Output)
    };
    int nleds = 4;
    Pin_All_On(leds, nleds);

    // Initialize serial port
    Serial_t port = Serial_Init(0, 9600);
    FILE * f = Serial_Get_File(port);

    // Send a string in non-blocking.  Only a part will be received
    uint32_t b = Serial_Put_Bytes(port, NONBLOCKING, "Hello World! How's it going? 0123456789ABCDEF\r\n", 47);

    // Send a formatted string using fprintf
    fprintf(f,"\r\nSent bytes: %d\r\n", b);
    fprintf(f,"File pointer: %p\r\n", f);

    // Send a long string. Complete
    Serial_Put_Bytes(port, BLOCKING, "Hello World! How's it going? 0123456789ABCDEF\r\n", 47);

    // Send strings in the background
    Serial_Put_Bytes(port, BACKGROUND, "This is a very long string being sent on background.\r\n", 54);
    Serial_Put_Bytes(port, BACKGROUND, "This is another long string being sent on background.\r\n", 55);
    Serial_Put_Bytes(port, BACKGROUND, "This is yet another long string being sent on background.\r\n", 59);
    Serial_Put_Bytes(port, BACKGROUND, "And this is yet another long string being sent on background.\r\n", 63);

    // Do something while the string is being sent
    uint32_t i;
    for (i = 0; i < 0xFFFFF; i++) {
        Pin_Show_Byte(leds, nleds, i >> 16);
    }

    // This string will only be sent once the others have been
    // completed.
    Serial_Put_Bytes(port, BLOCKING, "All strings sent, now echoing each key:\r\n", 41);

    // Repeat the received byte
    uint8_t buffer[1];
    while (1) {
        Serial_Get_Bytes(port, BLOCKING, buffer, 1);
        Pin_Show_Byte(leds, nleds, buffer[0]);
        Serial_Put_Bytes(port, BLOCKING, buffer, 1);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
