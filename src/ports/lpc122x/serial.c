/*
 * libmanyuc - Template serial communication file
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

#include "serial.h"
#include <stdlib.h>

// Convert the serial port number to a serial port struct.
Serial_t Serial_Get(int number) {
    Serial_t port;
    return port;
}

// Create a serial port structure and initialize it
Serial_t Serial_Init(int number, int baudrate) {

    Serial_t port = Serial_Get(number);

    return port;
}

// Returns a byte read from the serial port. If there is no byte yet, it
// blocks until there is.
inline char Serial_Get_Byte(Serial_t port) {
    return 0;
}

// Reads the amount of bytes from the serial port into the buffer.
// Memory for the buffer must have been allocated first.
uint32_t Serial_Get_Bytes(Serial_t port, SerialTransferMode mode, 
                          char *data, uint32_t length) {
    return 0;
}

// Sends a byte through the serial port. If there is no space, it blocks
// until there is.
inline void Serial_Put_Byte(Serial_t port, char data) {

}

// Send bytes in several different modes
uint32_t Serial_Put_Bytes(Serial_t port, SerialTransferMode mode, 
                          char *data, uint32_t length)  {
    return 0;
}

FILE *Serial_Get_File(Serial_t port) {
    return NULL;
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
