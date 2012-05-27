/*
 * libmanyuc - i2c cpp header file
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

#ifndef SERIAL_CPP_H
#define SERIAL_CPP_H

#include "serial.h"
#include <string.h>

class Serial {
private:
    Serial_t port;
public:
    
    /** Returns the serial port structure corresponding to the
     *  serial port number.  The pins corresponding to each serial
     *  port depend on the microcontroller.
     *
     *  @param number The serial port number in the microcontroller.
     *  @param baudrate The baudrate to initialize the port. 
                        Default: 9600.
     *  @return A serial port structure. The port is not initialized
     *  with this function.
     */
    Serial(int number, int baudrate=9600) {
        this->port = Serial_Get(number);
        Serial_Init(this->port, baudrate);
    }

    /** Returns one byte received through the serial port.
     *
     *  @return The byte received through the serial port.
     */
    uint8_t read() {
        return Serial_Get_Byte(this->port);
    }

    /** Transmits one byte through the serial port.
     *
     *  @param data The byte to be sent through the serial port.
     */
    void write(uint8_t data) {
        Serial_Put_Byte(this->port, data);
    }

    /** Transmits a byte buffer through the serial port.
     *
     *  @param port The serial port obtained through Serial_Get.
     *  @param data The bytes to be sent through the serial port.
     *  @param length The amount of bytes to be sent. This value
     *  must be less or equal to the length of the buffer.
     *  @param mode The transfer mode selected for this transmission.
     *   - BLOCKING: the function blocks until all bytes have been sent.
     *   - NONBLOCKING: the function leaves as soon as bytes can't be sent.
     *   - BLOCK_WITH_TIMEOUT: the function blocks but might terminate if
     *     the internal timeout is reached.
     *  @return the amount of bytes that could be actually written.
     */
    uint32_t write(uint8_t *data, uint32_t length, 
        SerialTransferMode mode=BLOCKING) {
        return Serial_Put_Bytes(this->port, data, length, mode);
    }

    void printf(char *data) {
        Serial_Put_Bytes(this->port, (uint8_t *) data, strlen(data), BLOCKING);
    }

};

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
