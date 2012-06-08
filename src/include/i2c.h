/**************************************************************************//**
 * @defgroup I2C I2C Communication
 * @{
 * @brief    libmanyuc I2C Communication definitions
 * @date     May 2012
 * @author   Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * @par
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * @par
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @par
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 *
 ******************************************************************************/

#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>
#include "board.h"

    /** Opaque structure to hold I2C device
     *  The data contained in the structure depends on the
     *  architecture. It should be created through I2C_Init.
     */
    typedef struct _i2c_t I2C_t;

    /** I2C Device modes */
    typedef enum I2CMode { I2CMaster, I2CSlave} I2CMode;

    /** Creates the I2C device structure needed to communicate through I2C
     *  @param port The I2C port number to use, the ports available depend on
     *  the architecture
     *  @param address The address to identify the device if in Slave mode, 0 otherwise.
     *  @param mode The I2C mode to use for this device (Master or Slave).
     *  @return A structure that represents an initialized I2C device.
     */
    I2C_t I2C_Init(uint8_t port, uint8_t address, I2CMode mode);

    /** Reads one byte from the I2C bus.
     *  @param device An initialized I2C device
     *  @param address The slave address when operating in Master mode, 0 if in
     *  Slave mode.
     *  @return The byte read from the bus
     */
    uint8_t I2C_Read_Byte(I2C_t device, uint8_t address);

    /** Reads any number of bytes from the I2C bus.
     *  @param device An initialized I2C device.
     *  @param address The slave address when operating in Master mode, 0 if in
     *  Slave mode.
     *  @param data A pointer to an initialized byte array.
     *  @param length The amount of bytes to read into the array.
     *  @return The amount of bytes actually read.
     */
    uint8_t I2C_Read_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length);

    /** Writes one byte to the I2C bus.
     *  @param device An initialized I2C device
     *  @param address The slave address when operating in Master mode, 0 if in
     *  Slave mode.
     *  @param data The byte to write to the bus.
     *  @return 1 if the write was acknowledged, 0 otherwise
     */
    uint8_t I2C_Write_Byte(I2C_t device, uint8_t address, uint8_t data);

    /** Writes any number of bytes to the I2C bus.
     *  @param device An initialized I2C device.
     *  @param address The slave address when operating in Master mode, 0 if in
     *  Slave mode.
     *  @param data A pointer to a byte array containing the data to send.
     *  @param length The amount of bytes to read from the array
     *  @return The amount of bytes actually written.
     */
    uint8_t I2C_Write_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length);

    /** Generate a start condition in the I2C bus.
     *  Only meaningful in Master mode.
     *  @param device An initialized I2C device.
     */
    void I2C_Start(I2C_t device);

    /** Transmit a stop condition to the I2C bus in Master mode,
     *  recover from errors in slave mode.
     *  @param device An initialized I2C device.
     */
    void I2C_Stop(I2C_t device);

    /** Sets the device address. Only relevant in slave mode.
     *  @param device An initialized I2C device.
     *  @param address The slave address to set.
     */
    void I2C_Address(I2C_t device, uint8_t address);

    /** Sets the bus frequency in hertz.
     *  @param device An initialized I2C device.
     *  @param hz The frequency to set in hertz.
     */
    void I2C_Frequency(I2C_t device, uint32_t hz);

//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
