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
Pin_t Pin_Get (PinName pin_name) {
	uint32_t address = pin_name - LPC_GPIO_BASE;
	Pin_t pin = { address / 32, address % 32, 1 << (address % 32) };
	return pin;
}

// Set pin input mode
void Pin_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
	uint32_t port = _get_half_port(pin);
	uint32_t shift = _get_half_mask(pin);

	// Set input type (PullUp, PullDown, PullNone)
    if (mode < 4) {
        LPC_PINCON->PINMODE[port] &= ~(3 << shift);
        LPC_PINCON->PINMODE[port] |= (mode << shift);
	// Set opendrain
    } else if (mode == OpenDrain) {
		_set_open_drain(pin.port, pin.mask);
    } else if (mode == NormalMode) {
		_set_normal_mode(pin.port, pin.mask);
	// Set pin primary / secondary / etc function.
	} else {
		mode -= 8;
		LPC_PINCON->PINSEL[port] &= ~(3 << shift);
		LPC_PINCON->PINSEL[port] |= (mode << shift);
	}
}

#include <stdarg.h>
PinBus_t vPinBus_Get(int npins, va_list pins) {
	int i;
	PinBus_t bus = { { {0,{0,0}}, {0,{0,0}}, {0,{0,0}}, } };

	for (i = 0; i < npins; i++) {
	    uint32_t address = va_arg(pins, uint32_t) - LPC_GPIO_BASE;
		uint8_t number = address % 32;
		// Add the pin to the 32 pin mask
		bus.ports[address / 32].mask |= 1 << number;
		// And the pin to the 16 pin mask with 2 bits per pin.
		if (number < 16) {
			bus.ports[address / 32].half_mask[0] |= 3 << (number*2);
		} else {
			bus.ports[address / 32].half_mask[1] |= 3 << ((number-16)*2);
		}
	}
    return bus;
}

void PinBus_Mode(PinBus_t bus, PinMode mode) {
// TODO: lock for concurrency
	if (mode == OpenDrain) {
		return _PinBus_Apply(bus, _set_open_drain);
	} else if (mode == NormalMode) {
		return _PinBus_Apply(bus, _set_normal_mode);
	}

	int i;
	// Create a 32bit mask that repeats the mode 16 times
	uint32_t mode_mask = mode & 0x3;
	for (i = 2; i < 32; i *= 2) {
		mode_mask = (mode_mask << i) + mode_mask;
	}

	int port;
	for (port = 0; port < MAX_PORTS; port++) {
		for (i = 0; i < 2; i++) {

			uint32_t pin_mask = bus.ports[port].half_mask[i];
			if (!pin_mask) continue;

			uint32_t value = pin_mask & mode_mask;
			uint8_t half_port = 2*port+i;
		    if (mode < 4) {
        		LPC_PINCON->PINMODE[half_port] &= ~(pin_mask);
		        LPC_PINCON->PINMODE[half_port] |= value;
			} else {
				LPC_PINCON->PINSEL[half_port] &= ~(pin_mask);
				LPC_PINCON->PINSEL[half_port] |= value;
			}
		}
	}
}

// Returns this arch's leds.
PinBus_t PinBus_Get_Notification() {
	return PinBus_Get(4, LED1, LED2, LED3, LED4);
}

/*

All this code is unused, replaced by the hash.

typedef struct _io_function {
	void (*rise)(void);
	void (*fall)(void);
} io_function;
uint8_t *io_interrupt_table = NULL;
io_function *io_interrupt_functions = NULL;
uint8_t io_interrupt_amount = 0;
// mask to enable/disable an interrupt.
#define IO_ENABLE_RISE_MASK  (1<<7)
#define IO_ENABLE_FALL_MASK  (1<<6)
	io_interrupt_table = calloc(NUM_IO_PINS*sizeof(uint8_t));

	// Increase the space for the functions
	io_function * aux = realloc(io_interrupt_functions, 
		(io_interrupt_amount + 1) * sizeof(io_function));
	if (aux == NULL) return;
	io_interrupt_functions = aux;

	// Store the new function
	if (mode == RISE) {
		io_interrupt_functions[io_interrupt_amount].rise = f;
		io_interrupt_functions[io_interrupt_amount].fall = NULL;
		io_interrupt_table[pos] = io_interrupt_amount | IO_ENABLE_RISE_MASK;
	} else {
		io_interrupt_functions[io_interrupt_amount].rise = NULL;
		io_interrupt_functions[io_interrupt_amount].fall = f;
		io_interrupt_table[pos] = io_interrupt_amount | IO_ENABLE_FALL_MASK;
	}
	
static void io_interrupt_set(uint8_t pos, void(*function)(void)) {
	
	// Store the new function
	if (mode == RISE) {
		io_interrupt_functions[io_interrupt_amount].rise = f;
		io_interrupt_functions[io_interrupt_amount].fall = NULL;
		io_interrupt_table[pos] = io_interrupt_amount | IO_ENABLE_RISE_MASK;
	} else {
		io_interrupt_functions[io_interrupt_amount].rise = NULL;
		io_interrupt_functions[io_interrupt_amount].fall = f;
		io_interrupt_table[pos] = io_interrupt_amount | IO_ENABLE_FALL_MASK;
	}
	
	// Increase the amount of stored functions
	io_interrupt_amount++;
}

static void io_interrupt_replace(uint8_t pos, void(*function)(void), IOIntMode mode) {
	uint8_t index = io_interrupt_table[pos] & IO_INT_POS_MASK;
	if (mode == RISE) {
		io_interrupt_table[pos] |= IO_ENABLE_RISE_MASK;
		io_interrupt_functions[index].rise = f;
	} else {
		io_interrupt_table[pos] |= IO_ENABLE_FALL_MASK;
		io_interrupt_functions[index].fall = f;
	}
void Pin_Int_Disable(struct _pin_t pin, IOIntMode mode) {
	if (mode == RISE) {
		io_interrupt_table[pos] &= ~(IO_ENABLE_RISE_MASK);
	} else {
		io_interrupt_table[pos] &= ~(IO_ENABLE_FALL_MASK);
	}
}}	
uint32_t io_interrupt_enable[4];
// Amount of pins that allow io interrupts.
#define IO_NUM_PINS     2*32
#define IO_INT_POS_MASK    (0x3F)
	
	*/
#include "hash.h"

Hash_t *io_interrupt_table = NULL;
typedef void (*io_int_func)(void);

// Returns the corresponding byte identification for the pin 
// address, port, and interrupt mode
static inline uint8_t io_interrupt_get_byte(uint32_t address, 
		uint8_t port, uint8_t mode) {
	uint8_t pos = address;
	pos += 32 * (port/2);
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
			io_interrupt_call_handlers(states, j, port*16);
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
	/*if (Hash_Len(io_interrupt_table) < 16) {
		Hash_Iter_t *iter = Hash_Iter_Init(io_interrupt_table);
		while (Hash_Iter_Has_Next(iter)) {
			Hash_Key_t key = Hash_Iter_Get_Next(iter);
			uint8_t port = (key & 0x20);
			uint8_t pos  = (key & 0x1F);
			if (port == 0) {
				io_interrupt_call_handlers((uint32_t*) LPC_GPIOINT->IO0IntStat, pos, 0);
			} else {
				io_interrupt_call_handlers((uint32_t*) LPC_GPIOINT->IO2IntStat, pos, 32);
			}
		}
		Hash_Iter_Destroy(iter);
	} 
	// If there are more than 16 interrupts registered, 
	// go through the interrupt state vectors.
	else { */
		io_interrupt_read_all((uint32_t*) LPC_GPIOINT->IO0IntStat, 0);
		io_interrupt_read_all((uint32_t*) LPC_GPIOINT->IO2IntStat, 2);
	/*}*/
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
	if ((pin.port != 0)	&& (pin.port != 2)) return;
		
	// Initialize the table if necessary
	if (io_interrupt_table == NULL) {
		io_interrupt_init();
	}

	// Get the byte for the hash
	uint8_t pos = io_interrupt_get_byte(pin.address, pin.port, mode);
	// Store the function pointer
	Hash_Set(io_interrupt_table, pos, (void*) function);

	Pin_Int_Enable(pin, mode);
}


