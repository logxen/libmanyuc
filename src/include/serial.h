/**************************************************************************//**
 * @defgroup Serial Serial Port
 * @{
 * @brief    libmanyuc Serial Port definitions.
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

#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

    /** Opaque structure to represent the serial port.
     *  The data contained in the structure depends on the
     *  architecture. It should always be created through
     *  Serial_Get.
     */
    typedef struct _serial_t Serial_t;

    /** Available transfer modes for the serial ports */
    typedef enum { BLOCKING, NONBLOCKING, BLOCK_WITH_TIMEOUT }
    SerialTransferMode;

    /** Returns the serial port structure corresponding to the
     *  serial port number.  The pins corresponding to each serial
     *  port depend on the microcontroller.
     *
     *  @param number The serial port number in the microcontroller.
     *  @return A serial port structure. The port is not initialized
     *  with this function.
     */
    Serial_t Serial_Get(int number);

    /** Initializes the serial port.  Each port must be initialized
     *  once in order to be used.
     *
     *  @param port The serial port obtained through Serial_Get.
     *  @param baudrate The intended baudrate for the serial port.
     */
    void Serial_Init(Serial_t port, int baudrate);

    /** Returns one byte received through the serial port.
     *
     *  @param port The serial port obtained through Serial_Get.
     *  @return The byte received through the serial port.
     */
    uint8_t Serial_Get_Byte(Serial_t port);

    /** Transmits one byte through the serial port.
     *
     *  @param port The serial port obtained through Serial_Get.
     *  @param data The byte to be sent through the serial port.
     */
    void Serial_Put_Byte(Serial_t port, uint8_t data);

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
    uint32_t Serial_Put_Bytes(Serial_t port, uint8_t *data, uint32_t length,
                              SerialTransferMode mode);

//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
