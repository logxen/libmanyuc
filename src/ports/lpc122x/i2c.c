/*
 * libmanyuc - Template I2C File
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

#include "i2c.h"

// Initialize an I2C communication 
I2C_t I2C_Init(uint8_t port, uint8_t address, I2CMode mode) {

    // Return the I2C device
    I2C_t device;
    return device;
}

// Read one byte from the device
uint8_t I2C_Read_Byte(I2C_t device, uint8_t address) {
    return 0;
}

// Read many bytes from the device
uint8_t I2C_Read_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length) {
    return 0
}

// Write one byte to the device
uint8_t I2C_Write_Byte(I2C_t device, uint8_t address, uint8_t data) {
    return 0
}

// Write many bytes to the device
uint8_t I2C_Write_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length) {
}

// Start communication
void I2C_Start(I2C_t device) {

}

// Stop communication
void I2C_Stop(I2C_t device) {

}

// Set the device's address
void I2C_Address(I2C_t device, uint8_t address) {

}

// Change the communication frequency
void I2C_Frequency(I2C_t device, uint32_t hz) {
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
