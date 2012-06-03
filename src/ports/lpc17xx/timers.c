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
#define HW_TIMER_MR_AMOUNT 4

#define SW_TIMER_ID 1
#define SW_TIMER_MR_AMOUNT 3

// Interrupt function prototype
typedef void (*timer_int_func)(void);

// Scheduled function prototype
typedef struct _timer_sch_t {
    timer_int_func func;
    uint32_t reload;
    uint8_t active;
    uint8_t used;
} timer_sch_t;

// Software timer structure
typedef struct _sw_timer_sch_t {
    uint32_t reload[SW_TIMER_MR_AMOUNT];
    uint32_t tc[SW_TIMER_MR_AMOUNT];
    uint8_t  amount[SW_TIMER_MR_AMOUNT];
    (timer_sch_t*) sch[SW_TIMER_MR_AMOUNT];
} sw_timer_sch_t;

// Store the id of the next scheduled task
static uint8_t _next_ts = 0;
// Array to access the timers used to schedule by hardware
static timer_sch_t *_hw_timer_sch[2] = { NULL, NULL };
// Structure that stores the timers to schedule by software
static sw_timer_sch_t *_sw_timer_sch = NULL;

// Array to access the 4 hardware timers
static LPC_TIM_TypeDef *_timers[4] = { LPC_TIM0, LPC_TIM1, LPC_TIM2, LPC_TIM3};


// Internal function to enable the hardware timer 
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
    for (; i < HW_TIMER_MR_AMOUNT; i++) {
        _timers[timer_id]->MR[i] = 0;
    }

    // Release reset
    _timers[timer_id]->TCR = TIMER_TCR_ENABLE; // enable the timer

    // Enable timer interrupts
    NVIC->ISER[0] = (uint32_t)(1 << (timer_id + 1));
}

// Set a match register and enable that interrupt
static inline void _timer_set_mr(uint8_t timer_id, uint8_t mr_id, uint32_t time_delay) {
    _timers[timer_id]->MR[mr_id] = _timers[timer_id]->TC + time_delay;
    _timers[timer_id]->MCR |= TIMER_MCR_INTERRUPT(mr_id);
}

// Create a scheduler structure and initialize hardware
static void _hw_timer_sch_init(uint8_t timer_id) {

    // Initialize internal structures
    _hw_timer_sch[timer_id] = calloc(HW_TIMER_MR_AMOUNT, sizeof(timer_sch_t));
    if (_hw_timer_sch[timer_id] == NULL) Show_Error();

    // Initilize hardware - the timers used for scheduling have an offset.
    _timer_init(timer_id + HW_TIMER_OFFSET);
}

// Create a software scheduler structure and initialize hardware
static void _sw_timer_sch_init() {

    // Initialize internal structures
    _sw_timer_sch = calloc(1, sizeof(sw_timer_sch_t));
    if (_sw_timer_sch == NULL) Show_Error();

    // Initilize hardware
    _timer_init(SW_TIMER_ID);
}

void _timer_sch_store (_timer_sch_t *timer_sch, timer_int_func func, 
        uint32_t time_delay, uint8_t repeat) {
        timer_sch->func = func;
        timer_sch->active = 1;
        timer_sch->used = 1;
        timer_sch->reload = repeat ? time_delay : 0;
}

// Create a scheduler
Scheduler_t Scheduler_Init(timer_int_func func, uint32_t time_delay, uint8_t repeat) {

    Scheduler_t scheduler = { 0, 0, 0 };

    if (_next_ts < (HW_TIMER_MR_AMOUNT * HW_TIMER_AMOUNT)) {
        uint8_t timer_id = _next_ts / HW_TIMER_MR_AMOUNT;
        uint8_t mr_id = _next_ts % HW_TIMER_MR_AMOUNT;

        // Check if this timer is initialized
        if (_hw_timer_sch[timer_id] == NULL) {
            _hw_timer_sch_init(timer_id);
        }

        // Store the scheduling structure
        _timer_sch_store(&(_hw_timer_sch[timer_id][mr_id]), 
                func, time_delay, repeat);

        // Store the hardware info
        _timer_set_mr(timer_id + HW_TIMER_OFFSET, mr_id, time_delay);
        _next_ts++;

        scheduler.timer_id = timer_id + HW_TIMER_OFFSET;
        scheduler.mr_id = mr_id;
    } 
    
    
    // Software controlled timer
    else {
        // Initialize if necessary
        if ( _sw_timer_sch == NULL ) {
           _sw_timer_sch_init(); 
        }
        
        // Look for the best slot to store the timer
        uint8_t mr_id = _sw_timer_sch_find_best_slot(time_delay);
        uint8_t sw_mr_id = _sw_timer_sch_store(mr_id, func, time_delay, repeat);

        scheduler.timer_id = SW_TIMER_ID;
        scheduler.mr_id = mr_id;
        scheduler.sw_mr_id = sw_mr_id;

    }
    return scheduler;

}

static inline void hw_timer_sch_handle_int(uint8_t timer_id) {

    // Get the current TC and the int vector for this timer
    uint32_t current_tc = _timers[timer_id]->TC;
    uint32_t ints = (0xF) & _timers[timer_id]->IR;

    // Clear current interrupts and timer interrupt
    _timers[timer_id]->IR = 0xF;
    NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));

    uint8_t scheduler_id = timer_id - HW_TIMER_OFFSET;
    uint8_t mr_id = 0;
    while (ints) {
        if (ints & 0x1) {
            _timers[timer_id]->IR |= (1 << mr_id);
            _timers[timer_id]->MR[mr_id] = current_tc +
                                           _hw_timer_sch[scheduler_id][mr_id].reload;
            _hw_timer_sch[scheduler_id][mr_id].func();
        }
        ints >>= 1;
        mr_id++;
        // Check to avoid missing interrupts - NOT WORKING
        if (!ints) {
            ints = (0xF) & _timers[timer_id]->IR;
            _timers[timer_id]->IR = 0xF;
            NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));
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
    hw_timer_sch_handle_int(2);
}


void TIMER3_IRQHandler() {
    hw_timer_sch_handle_int(3);
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
