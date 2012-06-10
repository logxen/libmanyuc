/*
 * libmanyuc - LPC serial communication file
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
#include "io.h"
#include <stdlib.h>

// Port tables

const static int modes[] = { S0_Mode, S1_Mode, S2_Mode, S3_Mode };
const static int power_bits[] = { PCUART0, PCUART1, PCUART2, PCUART3 };
const static uint32_t txs[] = { TX_0, TX_1, TX_2, TX_3 };
const static uint32_t rxs[] = { RX_0, RX_1, RX_2, RX_3 };
const static int uarts[] = { UART_0, UART_1, UART_2, UART_3 };

// Internal defines used for bit operations
#define UART_BYTE_MASK          ((uint8_t) 0xFF)      // Mask bit for byte data
#define UART_LSB(val)           ((val) & 0xFF)        // LSB of val
#define UART_MSB(val)           (((val) >> 8) & 0xFF) // MSB of val

#define UART_FCR_FIFO_EN        ((uint8_t)(1<<0))     // UART FIFO enable 
#define UART_FCR_RX_RS          ((uint8_t)(1<<1))     // UART FIFO RX reset 
#define UART_FCR_TX_RS          ((uint8_t)(1<<2))     // UART FIFO TX reset 

// Line status register
#define UART_LSR_RDR            ((uint8_t)(1<<0))     // LSR Receive data ready
#define UART_LSR_THRE           ((uint8_t)(1<<5))     // LSR Transmit holding register empty

// Transmit enable register
#define UART_TER_TXEN           ((uint8_t)(1<<7))     // Transmit enable bit

// Line control register
#define UART_LCR_WLEN5          ((uint8_t) 0)         // 5 bit character length 
#define UART_LCR_WLEN6          ((uint8_t) 1)         // 6 bit character length 
#define UART_LCR_WLEN7          ((uint8_t) 2)         // 7 bit character length 
#define UART_LCR_WLEN8          ((uint8_t) 3)         // 8 bit character length 
#define UART_LCR_STOPBIT_SEL    ((uint8_t)(1<<2))     // UART Two Stop Bits Select 
#define UART_LCR_PARITY_EN      ((uint8_t)(1<<3))     // UART Parity Enable/
#define UART_LCR_PARITY_ODD     ((uint8_t)(0))        // UART Odd Parity Select 
#define UART_LCR_PARITY_EVEN    ((uint8_t)(1<<4))     // UART Even Parity Select 
#define UART_LCR_PARITY_F_1     ((uint8_t)(2<<4))     // UART force 1 stick parity 
#define UART_LCR_PARITY_F_0     ((uint8_t)(3<<4))     // UART force 0 stick parity 
#define UART_LCR_BREAK_EN       ((uint8_t)(1<<6))     // UART Transmission Break enable 
#define UART_LCR_DLAB_EN        ((uint8_t)(1<<7))     // UART Divisor Latches Access bit enable

#define UART_TX_FIFO_SIZE       (16)                  // Size of the FIFO queue
#define UART_BLOCK_TIMEOUT      0xFFFFFFFF            // Timeout for blocking 

// Transmiter Holding Register Empty
#define UART_IER_THREINT_EN     ((uint32_t)(1<<1))  // THR Interrupt enable


static uint8_t serial_initialized[] = { 0, 0, 0, 0 };

/* Convert the serial port number to a serial port struct. */
Serial_t Serial_Get(int number) {
    if (number < 0 || number > 4) number = 0;
    Serial_t port = {
        Pin_Get(txs[number]),
        Pin_Get(rxs[number]),
        (LPC_UART_TypeDef *) uarts[number],
        number
    };
    return port;
}

Serial_t Serial_Init(int number, int baudrate) {

    Serial_t port = Serial_Get(number);
    if (serial_initialized[number] != 0) {
        return port;
    }
    serial_initialized[number] = 1;

    // 1 - Power up the serial port
    uint32_t power_bit_mask = 1 << power_bits[port.number];
    LPC_SC->PCONP |= power_bit_mask;

    // 3 - Set the baudrate
    uint32_t SystemCoreClock = 100000000;
    uint16_t rate = SystemCoreClock / (16 * 4 * baudrate);

    // Enable divisor latches and set the rate
    port.uart->LCR |= UART_LCR_DLAB_EN;
    port.uart->DLL = UART_LSB(rate);
    port.uart->DLM = UART_MSB(rate);

    // 4 - Empty FIFOs and Disable FIFO
    port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;
    port.uart->FCR = 0;
    /*
        // Read what was already on the buffers
        uint8_t aux;
        while (port.uart->LSR & UART_LSR_RDR) {
            aux = port.uart->RBR;
        }

        // Enable transmission
        port.uart->TER = UART_TER_TXEN;
        // Transmit what was already on the buffer
        while (!(port.uart->LSR & UART_LSR_THRE));
        // Disable transmission
        port.uart->TER = 0;

        // Enable FIFO
        port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;*/

    // 5 - Set the pin function
    Pin_Mode(port.tx, modes[port.number]);
    Pin_Mode(port.rx, modes[port.number]);

    // 6 - Disable Interrupts
    port.uart->IER = 0;

    // Reset LCR / ACR
    port.uart->LCR = 0;
    /*  port.uart->ACR = 0;

        // Read anything still on the buffers
        aux = port.uart->LSR;*/

    // Set configuration for transmission (8N1)
    /*port.uart->LCR = UART_LCR_WLEN8 | UART_LCR_BREAK_EN;*/
    port.uart->LCR = UART_LCR_WLEN8;

    port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;

    // Enable transmission
    port.uart->TER = UART_TER_TXEN;

    return port;
}

// Returns if there is info available to be read
inline int Serial_Readable(Serial_t port) {
    return (port.uart->LSR & UART_LSR_RDR);
}

// Returns a byte read from the serial port. If there is no byte yet, it
// blocks until there is.
inline char Serial_Get_Byte(Serial_t port) {
    return port.uart->RBR & UART_BYTE_MASK;
}

// Reads the amount of bytes from the serial port into the buffer.
// Memory for the buffer must have been allocated first.
uint32_t Serial_Get_Bytes(Serial_t port, SerialTransferMode mode, 
                          char *data, uint32_t length) {

    uint32_t i = 0, wait;

    while (i < length) {

        // If non blocking, check if there's something to read
        // and if not, bail out.
        if (!(Serial_Readable(port)) && (mode == NONBLOCKING)) {
            break;
        }
        wait = UART_BLOCK_TIMEOUT;
        while (!(Serial_Readable(port)) && (mode == BLOCKING || (wait > 0))) {
            wait--;
        }
        if (!wait) break;

        data[i] = Serial_Get_Byte(port);
        i++;

    }
    return i;
}

// Returns if there is space to send a byte
inline int Serial_Sendable(Serial_t port) {
    return (port.uart->LSR & UART_LSR_THRE);
}

// Sends a byte through the serial port. If there is no space, it blocks
// until there is.
inline void Serial_Put_Byte(Serial_t port, char data) {
    port.uart->THR = data & UART_BYTE_MASK;
}


static inline uint32_t _fill_fifo_queue(Serial_t port, char* data,
        uint32_t start, uint32_t end) {
    // Fill the fifo queue with bytes
    uint32_t c = UART_TX_FIFO_SIZE;
    while ((start < end) && (c > 0)) {
        Serial_Put_Byte(port, data[start]);
        start++;
        c--;
    }
    return start;
}

// Routines to send in the background
struct _to_send {
    char *data;
    uint32_t length;
    uint32_t sent;
};

static struct _to_send *_bgdata[] = {0, 0, 0, 0};

static void _send_data(int id) {

    if (!_bgdata[id]) return;

    Serial_t port = Serial_Get(id);
    _bgdata[id]->sent = _fill_fifo_queue(port, 
        _bgdata[id]->data,
        _bgdata[id]->sent,
        _bgdata[id]->length);

    // Check if the transmission was completed
    if (_bgdata[id]->sent >= _bgdata[id]->length) {
        // Free memory
        free(_bgdata[id]);
        _bgdata[id] = 0;
        // Disable interrupts
        port.uart->IER = 0;
        NVIC->ICER[0] = (1 << (5 + port.number));
    }
}

static void _background_send(Serial_t port, char *data, 
    uint32_t length) {

    // Disable interrupts to prevent possible concurrency problems
    NVIC->ICER[0] = (1 << (5 + port.number));

    // Allows accesing the IER register
    port.uart->LCR &= ~(UART_LCR_DLAB_EN);

    if (!_bgdata[port.number]) {
        _bgdata[port.number] = calloc(1, sizeof(struct _to_send));
    }

    // Add new data
    struct _to_send *bgdata = _bgdata[port.number];
    bgdata->data = realloc(bgdata->data, bgdata->length + length);
    uint32_t i, base_length = bgdata->length;
    for (i = 0; i < length; i++) {
        bgdata->data[i+base_length] = data[i];
    }
    bgdata->length += length;

    // If it's possible to send something, send it now
    if (Serial_Sendable(port)) {
        _send_data(port.number);
    }

    // Enable interrupts
    port.uart->IER = UART_IER_THREINT_EN;
    NVIC->ISER[0] = (1 << (5 + port.number));
}

// Send bytes in several different modes
uint32_t Serial_Put_Bytes(Serial_t port, SerialTransferMode mode, 
                          char *data, uint32_t length)  {

    uint32_t i = 0, wait;

    if (mode == BACKGROUND) {
        _background_send(port, data, length);
        return 0;
    }

    while (i < length) {

        // If non blocking, check for space and leave when none.
        if (!(Serial_Sendable(port)) && (mode == NONBLOCKING)) {
            break;
        }

        // Otherwise check for space according to the timeout, or not.
        wait = UART_BLOCK_TIMEOUT;
        while (!(Serial_Sendable(port)) && (mode == BLOCKING || (wait > 0))) {
            wait--;
        }
        if (!wait) break;

        i = _fill_fifo_queue(port, data, i, length);

    }
    // Return the amount of bytes that were sent
    return i;
}

static FILE* _serial_files[] = { 0, 0, 0, 0 };
FILE *Serial_Get_File(Serial_t port) {
    if (! _serial_files[port.number]) {
        _serial_files[port.number] = fdopen(0x0100 | port.number, "r+");
    }
    return _serial_files[port.number];
}


void UART0_IRQHandler() {
    _send_data(0);
}

void UART1_IRQHandler() {
    _send_data(1);
}

void UART2_IRQHandler() {
    _send_data(2);
}

void UART3_IRQHandler() {
    _send_data(3);
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
