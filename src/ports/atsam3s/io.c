/*
 * libmanyuc - LPC io file
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
#include "board.h"

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get(PinName pin_name) {
    Pin_t pin = { pin_name / 32, pin_name % 32, 1 << (pin_name % 32) };
    return pin;
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
    _set_input_mode(pin.port, pin.mask, mode);
}

#include <stdarg.h>
PinBus_t vPinBus_Get(int npins, va_list pins) {
    int i;
    PinBus_t bus = { { {0}, {0}, {0}, {0} } };

    for (i = 0; i < npins; i++) {
        uint32_t address = va_arg(pins, uint32_t);
        uint8_t number = address % 32;
        // Add the pin to the 32 pin mask
        bus.ports[address / 32].mask |= 1 << number;
    }
    return bus;
}

void PinBus_Mode(PinBus_t bus, PinMode mode) {
// TODO: lock for concurrency
    int port;
    for (port = 0; port < MAX_PORTS; port++) {
        if (bus.ports[port].mask) {
            _set_input_mode(port, bus.ports[port].mask, mode);
        }
    }
}

// Returns this arch's leds.
PinBus_t PinBus_Get_Notification() {
    return PinBus_Get(4, LED1, LED2, LED3, LED4);
}

/*

#include "hash.h"

Hash_t *io_interrupt_table = NULL;
typedef void (*io_int_func)(void);

// Returns the corresponding byte identification for the pin
// address, port, and interrupt mode
static inline uint8_t io_interrupt_get_byte(uint32_t address,
uint8_t port, uint8_t mode) {
    uint8_t pos = address;
    pos += 32 * (port / 2);
    pos += 64 * (mode);
    return pos;
}

// Call both handlers (if apropriate) and clear the interrupts
static inline void io_interrupt_call_handlers(uint32_t *states, uint8_t id, uint8_t port_mask) {
    uint32_t mask = (1 << id);
    io_int_func f = NULL;
    if (states[0] & mask) {
        f = (io_int_func) Hash_Get(io_interrupt_table, id + port_mask);
        if (f != NULL) f();
    }
    if (states[1] & mask) {
        f = (io_int_func) Hash_Get(io_interrupt_table, id + port_mask + 64);
        if (f != NULL) f();
    }
    states[2] |= mask;
}

// Iterate over a register of interrupts, calling the functions
static void io_interrupt_read_all(uint32_t *states,  uint8_t port) {

    uint32_t ints = states[0] | states[1];
    uint8_t j = 0;

    while (ints != 0) {
        if (ints & 0x1) {
            io_interrupt_call_handlers(states, j, port * 16);
        }
        ints >>= 1;
        j++;
    }
}

void EINT3_IRQHandler(void) {

    // TODO: this could probably be done better.  Some strategies:
    // 1 - if the amount of interrupts is small, iterate the hash items and check them.
    // 2 - go through the 32bit register as if it were a tree, using pre-codified masks.
    // 3 - OR the 4 words, shift the result and when finding a 1 check the 4 registers.
    if (io_interrupt_table == NULL) return;

    // If there are less than 16 interrupts registered,
    // go through the list and check all of them
    io_interrupt_read_all((uint32_t *) LPC_GPIOINT->IO0IntStat, 0);
    io_interrupt_read_all((uint32_t *) LPC_GPIOINT->IO2IntStat, 2);
}

// Initializes the interrupt table
static void io_interrupt_init() {
    io_interrupt_table = Hash_Init(NULL);
    NVIC->ISER[0] |= (1 << EINT3_IRQn);
}

void Pin_Int_Enable(struct _pin_t pin, IOIntMode mode) {
    // Enable the interrupt in the microcontroller
    if (pin.port == 0) {
        LPC_GPIOINT->IO0IntEn[mode] |= pin.mask;
    } else {
        LPC_GPIOINT->IO2IntEn[mode] |= pin.mask;
    }
}

void Pin_Int_Disable(struct _pin_t pin, IOIntMode mode) {
    // Disable the interrupt in the microcontroller
    if (pin.port == 0) {
        LPC_GPIOINT->IO0IntEn[mode] &= ~(pin.mask);
    } else {
        LPC_GPIOINT->IO2IntEn[mode] &= ~(pin.mask);
    }
}

void Pin_Int_Attach(struct _pin_t pin, void(*function)(void), IOIntMode mode) {

    // Only allow ports 0 and 2 in the LPC arch.
    if ((pin.port != 0) && (pin.port != 2)) return;

    // Initialize the table if necessary
    if (io_interrupt_table == NULL) {
        io_interrupt_init();
    }

    // Get the byte for the hash
    uint8_t pos = io_interrupt_get_byte(pin.address, pin.port, mode);
    // Store the function pointer
    Hash_Set(io_interrupt_table, pos, (void *) function);

    Pin_Int_Enable(pin, mode);
}

*/
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
