/*
 * libmanyuc - i2c cpp file
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

I2C::I2C(uint8_t port, uint8_t address, I2CMode mode) {
    this->device = I2C_Init(port, address, mode);
}

uint8_t I2C::read() {
    return I2C_Read_Byte(this->device, 0);
}

uint8_t I2C::read(uint8_t address) {
    return I2C_Read_Byte(this->device, address);
}

uint8_t I2C::read(uint8_t *data, uint8_t length) {
    return I2C_Read_Bytes(this->device, 0, data, length);
}

uint8_t I2C::read(uint8_t address, uint8_t *data, uint8_t length) {
    return I2C_Read_Bytes(this->device, address, data, length);
}

uint8_t I2C::write(uint8_t data) {
    return I2C_Write_Byte(this->device, 0, data);
}

uint8_t I2C::write(uint8_t address, uint8_t data) {
    return I2C_Write_Byte(this->device, address, data);
}

uint8_t I2C::write(uint8_t *data, uint8_t length) {
    return I2C_Write_Bytes(this->device, 0, data, length);
}

uint8_t I2C::write(uint8_t address, uint8_t *data, uint8_t length) {
    return I2C_Write_Bytes(this->device, address, data, length);
}

void I2C::start() {
    I2C_Start(this->device);
}

void I2C::stop() {
    I2C_Stop(this->device);
}

void I2C::address(uint8_t address) {
    I2C_Address(this->device, address);
}

void I2C::frequency(uint32_t hz) {
    I2C_Frequency(this->device, hz);
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
