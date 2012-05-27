/*
 * libmanyuc - LPC PWM File
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

#include "port.h"

#define I2C_I2CONSET_AA             ((0x04)) // Assert acknowledge flag
#define I2C_I2CONSET_SI             ((0x08)) // I2C interrupt flag
#define I2C_I2CONSET_STO            ((0x10)) // STOP flag
#define I2C_I2CONSET_STA            ((0x20)) // START flag 
#define I2C_I2CONSET_I2EN           ((0x40)) // I2C interface enable 

#define I2C_I2CONCLR_AAC            ((1<<2)) // Assert Acknowledge Clear bit 
#define I2C_I2CONCLR_SIC            ((1<<3)) // I2C interrupt Clear bit
#define I2C_I2CONCLR_STAC           ((1<<5)) // START flag Clear bit
#define I2C_I2CONCLR_I2ENC          ((1<<6)) // I2C interface Disable bit

#define I2C_I2DAT_BITMASK           ((0xFF))
#define I2C_I2ADR_GC                ((1<<0))
#define I2C_I2ADR_BITMASK           ((0xFF))


// Internal tables to select ports
const static uint8_t power_bit[] = { 7, 19, 26 };
const static uint8_t modes[]     = { Alt1, Alt3, Alt2 };
const static uint32_t sdas[]     = { SDA0, SDA1, SDA2 };
const static uint32_t scls[]     = { SCL0, SCL1, SCL2 };
static LPC_I2C_TypeDef *const i2c_devs[] = {LPC_I2C0, LPC_I2C1, LPC_I2C2};

// external variable set on port.c
extern uint32_t PeripheralClock;

// Clear start if set
static inline void _clear_start(uint8_t port) {
    if (i2c_devs[port]->I2CONSET & I2C_I2CONSET_STA) {
        i2c_devs[port]->I2CONCLR = I2C_I2CONCLR_STAC;
    }
}
// Set the clock frequency
static inline void _set_clock(uint8_t port, uint32_t hz) {
    uint32_t value = PeripheralClock / hz;
    i2c_devs[port]->I2SCLH = (uint32_t)(value / 2);
    i2c_devs[port]->I2SCLL = (uint32_t)(value - i2c_devs[port]->I2SCLH);
}

static inline uint8_t _send_byte(uint8_t port, uint8_t data) {
    _clear_start(port);
    // Set data to send
    i2c_devs[port]->I2DAT = data & I2C_I2DAT_BITMASK;
    // Clear SI
    i2c_devs[port]->I2CONCLR = I2C_I2CONCLR_SIC;
    // Wait until ready
    while (!(i2c_devs[port]->I2CONSET & I2C_I2CONSET_SI));
    // Return 1 if ACK, 0 if NACK
    return (i2c_devs[port]->I2STAT & 0x08 ? 1 : 0);
}

static inline uint8_t _recv_byte(uint8_t port) {
    // Send ACK
    i2c_devs[port]->I2CONSET = I2C_I2CONSET_AA;
    // Clear SI
    i2c_devs[port]->I2CONCLR = I2C_I2CONCLR_SIC;
    // Wait for SI
    while (!(i2c_devs[port]->I2CONSET & I2C_I2CONSET_SI));
    // Read data
    uint8_t data = (uint8_t)(i2c_devs[port]->I2DAT & I2C_I2DAT_BITMASK);
    return data;
}

static inline void _send_address(uint8_t port, uint8_t address, uint8_t read) {
    if (address) {
        _send_byte(port, (address << 1) | read);
    }
}

I2C_t I2C_Init(uint8_t port, uint8_t address, I2CMode mode) {
    if (port > 2) Show_Error();

    Pin_t sda = Pin_Get(sdas[port]);
    Pin_t scl = Pin_Get(scls[port]);

    // Set function
    Pin_Mode(sda, modes[port]);
    Pin_Mode(scl, modes[port]);

    // Set input mode
    Pin_Mode(sda, PullNone);
    Pin_Mode(scl, PullNone);
    Pin_Mode(sda, OpenDrain);
    Pin_Mode(scl, OpenDrain);

    // Give power to the device
    LPC_SC->PCONP |= (uint32_t)(1 << power_bit[port]);

    // Store initialization values
    if (mode == I2CMaster) {
        _set_clock(port, 100000);
    } else {
        i2c_devs[port]->I2ADR0 = (uint32_t) address;
    }

    // Clear AAC, Start, SI
    i2c_devs[port]->I2CONCLR = (I2C_I2CONCLR_AAC | I2C_I2CONCLR_STAC | I2C_I2CONCLR_SIC);
    // Enable
    i2c_devs[port]->I2CONSET = I2C_I2CONSET_I2EN;

    // Return the I2C device
    I2C_t device = { port, address, mode };
    return device;
}

uint8_t I2C_Read_Byte(I2C_t device, uint8_t address) {
    _send_address(device.port, address, 0x01);
    return _recv_byte(device.port);
}

uint8_t I2C_Read_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length) {
    _send_address(device.port, address, 0x01);
    int i = 0;
    for (; i < length; i++) {
        data[i] = _recv_byte(device.port);
    }
    return i;
}

uint8_t I2C_Write_Byte(I2C_t device, uint8_t address, uint8_t data) {
    _send_address(device.port, address, 0);
    return _send_byte(device.port, data);
}

uint8_t I2C_Write_Bytes(I2C_t device, uint8_t address, uint8_t *data, uint8_t length) {
    _send_address(device.port, address, 0);
    int i = 0;
    for (; i < length; i++) {
        _send_byte(device.port, data[i]);
    }
    return i;
}

void I2C_Start(I2C_t device) {

    // Set the start bit
    i2c_devs[device.port]->I2CONSET = I2C_I2CONSET_STA;
    // Clear the SI bit
    i2c_devs[device.port]->I2CONCLR = I2C_I2CONCLR_SIC;

    // Wait for complete
    while (!(i2c_devs[device.port]->I2CONSET & I2C_I2CONSET_SI));
    // Clear start bit
    i2c_devs[device.port]->I2CONCLR = I2C_I2CONCLR_STAC;
}

void I2C_Stop(I2C_t device) {

    _clear_start(device.port);
    // Set stop
    i2c_devs[device.port]->I2CONSET = I2C_I2CONSET_STO;
    // Clear SI
    i2c_devs[device.port]->I2CONCLR = I2C_I2CONCLR_SIC;

}

void I2C_Address(I2C_t device, uint8_t address) {
    // TODO
}


void I2C_Frequency(I2C_t device, uint32_t hz) {
    _set_clock(device.port, hz);
}

