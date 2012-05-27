/*
 * libmanyuc - LPC Timers
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
#include <stdlib.h>

// Power register
#define TIMER_POWER_BITMASK(n)  ((uint32_t) 1 << ((n<2)?(n+1):(n+20)))

// TCR
#define TIMER_TCR_ENABLE        ((uint32_t) 1 << 0)
#define TIMER_TCR_RESET         ((uint32_t) 1 << 1)

// MCR
#define TIMER_MCR_INTERRUPT(n)     ((uint32_t) 1 << (n*3))

#define HW_TIMER_AMOUNT 2
#define HW_TIMER_OFFSET 2
#define MR_AMOUNT 4

typedef void (*timer_int_func)(void);

typedef struct _timer_scheduler_t {
	timer_int_func func;
	uint32_t reload;
	uint8_t active;
	uint8_t used;
} timer_scheduler_t;

static uint8_t _next_ts = 0;
static timer_scheduler_t *_timer_scheduler[2] = { NULL, NULL };
static LPC_TIM_TypeDef *_timers[4] = { LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};

static inline void _timer_init(uint8_t timer_id) {

	LPC_SC->PCONP |= TIMER_POWER_BITMASK(timer_id); // enable power
	_timers[timer_id]->TCR = TIMER_TCR_RESET;       // reset the timer

	_timers[timer_id]->PR   = 24;   // Cycle at 1 us
	_timers[timer_id]->CCR  = 0;    // do not use capture
	_timers[timer_id]->CTCR = 0;    // use timer as counter
	_timers[timer_id]->MCR  = 0;    // disable all notifications
	_timers[timer_id]->IR   = 0xFF; // clear all interrupts
	
	// Set all registers to 0.
	int i = 0;
	for (; i < MR_AMOUNT; i++) {
		_timers[timer_id]->MR[i] = 0;
	}

	// Release reset
	_timers[timer_id]->TCR = TIMER_TCR_ENABLE; // enable the timer

	// Enable timer interrupts
	NVIC->ISER[0] = (uint32_t) (1<<(timer_id+1));
}

static inline void _timer_set_mr(uint8_t timer_id, uint8_t mr_id, uint32_t time_delay) {
	_timers[timer_id]->MR[mr_id] = _timers[timer_id]->TC + time_delay;
	_timers[timer_id]->MCR |= TIMER_MCR_INTERRUPT(mr_id);
}

static void _timer_scheduler_init(uint8_t timer_id) {

	// Initialize internal structures
	_timer_scheduler[timer_id] = calloc (MR_AMOUNT, sizeof(timer_scheduler_t));
	if (_timer_scheduler[timer_id] == NULL) Show_Error();

	// Initilize hardware
	_timer_init(timer_id + HW_TIMER_OFFSET); // The scheduling timers are off by one
}


Scheduler_t Scheduler_Init(timer_int_func func, uint32_t time_delay, uint8_t repeat) {

	Scheduler_t scheduler = { 0, 0 };

	if (_next_ts < MR_AMOUNT * HW_TIMER_AMOUNT) {
		uint8_t timer_id = _next_ts / MR_AMOUNT;
		uint8_t mr_id = _next_ts % MR_AMOUNT;

		// Check if this timer is initialized
		if (_timer_scheduler[timer_id] == NULL) {
			_timer_scheduler_init(timer_id);
		}

		// Store the scheduling structure
		_timer_scheduler[timer_id][mr_id].func = func;
		_timer_scheduler[timer_id][mr_id].active = 1;
		_timer_scheduler[timer_id][mr_id].used = 1;
		_timer_scheduler[timer_id][mr_id].reload = repeat ? time_delay : 0;

		// Store the hardware info
		_timer_set_mr(timer_id + HW_TIMER_OFFSET, mr_id, time_delay);
		_next_ts++;	
		
		scheduler.timer_id = timer_id;
		scheduler.mr_id = mr_id;
	} else {
		// TODO: Software controlled timer
	}
	return scheduler;

}

static inline void timer_scheduler_handle_int(uint8_t timer_id) {
	
	// Get the current TC and the int vector for this timer
	uint32_t current_tc = _timers[timer_id]->TC;
	uint32_t ints = (0xF) & _timers[timer_id]->IR;
	
	// Clear current interrupts and timer interrupt
	_timers[timer_id]->IR = 0xF;
	NVIC->ICPR[0] = (uint32_t) (1<<(timer_id+1));

	uint8_t scheduler_id = timer_id - HW_TIMER_OFFSET;
	uint8_t mr_id = 0;
	while (ints) {
		if (ints & 0x1) {
			_timers[timer_id]->IR |= (1 << mr_id);
			_timers[timer_id]->MR[mr_id] = current_tc + 
				_timer_scheduler[scheduler_id][mr_id].reload;
			_timer_scheduler[scheduler_id][mr_id].func();
		}
		ints >>= 1;
		mr_id++;
		// Check to avoid missing interrupts - NOT WORKING
		if (!ints) {
			ints = (0xF) & _timers[timer_id]->IR;
			_timers[timer_id]->IR = 0xF;
			NVIC->ICPR[0] = (uint32_t) (1<<(timer_id+1));
			mr_id = 0;
		}
	}
}


void TIMER0_IRQHandler() {
	// For counting - not used for timers
}	

void TIMER1_IRQHandler() {
	// For software timers
}	


void TIMER2_IRQHandler() {
	timer_scheduler_handle_int(2);
}	


void TIMER3_IRQHandler() {
	timer_scheduler_handle_int(3);
}	
