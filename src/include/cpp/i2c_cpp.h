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

#ifndef I2C_CPP_H
#define I2C_CPP_H

#include "port.h"

/** The i2c class represents an I2C device, either Master or Slave.
 *
 *  @author Margarita Manterola
 *  @date May 2012
 */

class I2C {
private:
    I2C_t device;
public:
    /** I2C Device Constructor.
     *  @param port The I2C port number to use, the ports available depend on
     *              the architecture
     *  @param mode The I2C mode to use for this device (Master or Slave).
     *              Master is the default mode, set if omitted.
     *  @param address The address to identify the device if in Slave mode, 0 if omitted.
     */
    I2C(uint8_t port, uint8_t address = 0, I2CMode mode = I2CMaster) {
        this->device = I2C_Init(port, address, mode);
    }

    /* === Reading for Slaves === */

    /** Reads one byte from the I2C bus.
     *  @return The byte read from the bus
     */
    uint8_t read() {
        return I2C_Read_Byte(this->device, 0);
    }

    /** Reads any number of bytes from the I2C bus.
     *  @param data A pointer to an initialized byte array.
     *  @param length The amount of bytes to read into the array.
     *  @return The amount of bytes actually read.
     */
    uint8_t read(uint8_t *data, uint8_t length) {
        return I2C_Read_Bytes(this->device, 0, data, length);
    }


    /* === Reading for Masters === */

    /** Reads one byte from the I2C bus.
     *  @param address The slave address when operating in
     *                 Master mode, ignored if in Slave mode.
     *  @return The byte read from the bus
     */
    uint8_t read(uint8_t address) {
        return I2C_Read_Byte(this->device, address);
    }

    /** Reads any number of bytes from the I2C bus.
     *  @param address The slave address when operating in Master mode,
     *                 ignored if in Slave mode.
     *  @param data A pointer to an initialized byte array.
     *  @param length The amount of bytes to read into the array.
     *  @return The amount of bytes actually read.
     */
    uint8_t read(uint8_t address, uint8_t *data, uint8_t length) {
        return I2C_Read_Bytes(this->device, address, data, length);
    }

    /* === Writing for Slaves === */

    /** Writes one byte to the I2C bus.
     *  @param data The byte to write to the bus.
     *  @return 1 if the write was acknowledged, 0 otherwise
     */
    uint8_t write(uint8_t data) {
        return I2C_Write_Byte(this->device, 0, data);
    }

    /** Writes any number of bytes to the I2C bus.
     *  @param data A pointer to a byte array containing the data to send.
     *  @param length The amount of bytes to read from the array
     *  @return The amount of bytes actually written.
     */
    uint8_t write(uint8_t *data, uint8_t length) {
        return I2C_Write_Bytes(this->device, 0, data, length);
    }

    /* === Writing for Masters === */

    /** Writes one byte to the I2C bus.
     *  @param address The slave address when operating in Master mode,
     *                 ignored if in Slave mode.
     *  @param data The byte to write to the bus.
     *  @return 1 if the write was acknowledged, 0 otherwise
     */
    uint8_t write(uint8_t address, uint8_t data) {
        return I2C_Write_Byte(this->device, address, data);
    }

    /** Writes any number of bytes to the I2C bus.
     *  @param address The slave address when operating in Master mode,
     *                 ignored if in Slave mode.
     *  @param data A pointer to a byte array containing the data to send.
     *  @param length The amount of bytes to read from the array
     *  @return The amount of bytes actually written.
     */
    uint8_t write(uint8_t address, uint8_t *data, uint8_t length) {
        return I2C_Write_Bytes(this->device, address, data, length);
    }

    /** Generate a start condition in the I2C bus.
     *  Only meaningful in Master mode.
     */
    void start() {
        I2C_Start(this->device);
    }

    /** Transmit a stop condition to the I2C bus in Master mode,
     *  recover from errors in slave mode.
     */
    void stop() {
        I2C_Stop(this->device);
    }

    /** Sets the device address. Only relevant in slave mode.
     *  @param address The slave address to set.
     */
    void address(uint8_t address) {
        I2C_Address(this->device, address);
    }

    /** Sets the bus frequency in hertz.
     *  @param hz The frequency to set in hertz.
     */
    void frequency(uint32_t hz) {
        I2C_Frequency(this->device, hz);
    }

};

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
