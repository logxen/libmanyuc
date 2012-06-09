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

#include "timers.h"
#include "board.h"
#include "swtimer.h"
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

// Scheduled function prototype
typedef struct _timer_sch_t {
    Int_Func func;
    uint32_t reload;
    uint8_t active;
    uint8_t used;
} timer_sch_t;

// Store the id of the next scheduled task
static uint8_t _next_ts = 0;
// Array to access the timers used to schedule by hardware
static timer_sch_t *_sch_timers[4] = { NULL, NULL, NULL, NULL };
// Structure that stores the timers to schedule by software
static SWTimer_t *_swtimer = NULL;

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

// Update a MR when a reload value changes
static inline void _timer_update_mr(uint8_t timer_id, uint8_t mr_id, 
    uint32_t time_delay) {

    // Get the needed numbers
    uint32_t tc = _timers[timer_id]->TC;
    uint32_t old_mr = _timers[timer_id]->MR[mr_id];

    // Store new value
    _timers[timer_id]->MR[mr_id] = tc + time_delay;

    // Update software ticker
    if (timer_id == SW_TIMER_ID) {
        uint32_t spent = (tc - (old_mr - _sch_timers[timer_id][mr_id].reload));
        SWTimer_TickMany(_swtimer, mr_id, spent/time_delay);
    }
}

// Create a scheduler structure and initialize hardware
static inline void _sch_timers_init(uint8_t timer_id) {
    // Initialize internal structures
    _sch_timers[timer_id] = calloc(HW_TIMER_MR_AMOUNT, sizeof(timer_sch_t));
    if (_sch_timers[timer_id] == NULL) Show_Error();
    // Initilize hardware - the timers used for scheduling have an offset.
    _timer_init(timer_id);
}

void _timer_sch_store (timer_sch_t *timer_sch, Int_Func func, 
    uint32_t time_delay, uint8_t repeat) {
    timer_sch->func = func;
    timer_sch->active = 1;
    timer_sch->used = 1;
    timer_sch->reload = repeat ? time_delay : 0;
}

// Create a scheduler
Scheduler_t Scheduler_Init_us(Int_Func func, uint32_t time_delay, 
        uint8_t repeat) {

    uint32_t timer_id = 0;
    uint32_t mr_id = 0;
    uint32_t sw_mr_id = 0;

    if (_next_ts < (HW_TIMER_MR_AMOUNT * HW_TIMER_AMOUNT)) {
        timer_id = (_next_ts % HW_TIMER_AMOUNT) + HW_TIMER_OFFSET;
        mr_id    = _next_ts / HW_TIMER_AMOUNT;
        _next_ts++;
    } else {
        if ( _swtimer == NULL ) {
            _swtimer = SWTimer_Init(SW_TIMER_MR_AMOUNT);
        }
        
        // Modify values appropriately
        timer_id = SW_TIMER_ID;
        mr_id = SWTimer_Store(_swtimer, func, time_delay, repeat,
            &sw_mr_id);
        time_delay = SWTimer_Get_Reload(_swtimer, mr_id);
        func = NULL;
        repeat = 1;
    }

    // Check if this timer is initialized
    if (_sch_timers[timer_id] == NULL) {
        _sch_timers_init(timer_id);
    }

    Scheduler_t scheduler = { timer_id, mr_id, sw_mr_id };

    if (sw_mr_id == 0) {
        _timer_set_mr(timer_id, mr_id, time_delay);
    } else {
        _timer_update_mr(timer_id, mr_id, time_delay);
    }

    // Store the scheduling structure
    _timer_sch_store(&(_sch_timers[timer_id][mr_id]), 
            func, time_delay, repeat);

    return scheduler;
}

/* Alternative version of the int handler that loses ints. */
static inline void timer_sch_handle_int(uint8_t timer_id, uint8_t sw) {

    // Get the current TC and the int vector for this timer
    uint32_t current_tc = _timers[timer_id]->TC;
    uint32_t ints = (0xF) & _timers[timer_id]->IR;

    // Clear current interrupts and timer interrupt
    _timers[timer_id]->IR = 0xF;
    NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));

    uint8_t mr_id = 0;
    while (ints) {
        if (ints & 0x1) {
            _timers[timer_id]->MR[mr_id] = current_tc +
                _sch_timers[timer_id][mr_id].reload;
            if (sw) {
                SWTimer_Tick(_swtimer, mr_id);
            } else {
                _sch_timers[timer_id][mr_id].func();
            }
        }
        ints >>= 1;
        mr_id++;
    
        // Check to avoid missing interrupts - NOT WORKING
/*        if (!ints) {
            ints = (0xF) & _timers[timer_id]->IR;
            _timers[timer_id]->IR = 0xF;
            NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));
            mr_id = 0;
        }*/
    }
}

static inline void hw_timer_sch_handle_int(uint8_t timer_id) {

    // Get the current TC and the int vector for this timer
    uint32_t current_tc = _timers[timer_id]->TC;
    uint32_t ints = (0xF) & _timers[timer_id]->IR;

    // Clear current interrupts and timer interrupt
    _timers[timer_id]->IR = 0xF;
    NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));

    uint8_t mr_id = 0;
    for (mr_id = 0; mr_id < HW_TIMER_MR_AMOUNT; mr_id++) {
        timer_sch_t sch = _sch_timers[timer_id][mr_id];
        if ((ints & 1 << mr_id) || 
            (sch.active && _timers[timer_id]->MR[mr_id] <= current_tc)) {
            if (sch.reload) {
                _timers[timer_id]->MR[mr_id] = current_tc + sch.reload;
            } else {
                sch.active = 0;
            }
            sch.func();
        }
    }
}

static inline void sw_timer_sch_handle_int(uint8_t timer_id) {

    // Get the current TC and the int vector for this timer
    uint32_t current_tc = _timers[timer_id]->TC;

    // Clear current interrupts and timer interrupt
    _timers[timer_id]->IR = 0xF;
    NVIC->ICPR[0] = (uint32_t)(1 << (timer_id + 1));

    uint8_t mr_id = 0;
    for (mr_id = 0; mr_id < SW_TIMER_MR_AMOUNT; mr_id++) {
        timer_sch_t sch = _sch_timers[timer_id][mr_id];
        if (sch.active && _timers[timer_id]->MR[mr_id] <= current_tc) {
            _timers[timer_id]->MR[mr_id] = current_tc + sch.reload;
            SWTimer_Tick(_swtimer, mr_id);
        }
    }
}

void TIMER0_IRQHandler() {
    // For counting - not used for timers
}

void TIMER1_IRQHandler() {
    sw_timer_sch_handle_int(1);
}

void TIMER2_IRQHandler() {
    hw_timer_sch_handle_int(2);
}

void TIMER3_IRQHandler() {
    hw_timer_sch_handle_int(3);
}


// SysTick Handler
volatile uint32_t msTicks;      /* counts 1ms timeTicks */
void SysTick_Handler(void) {
    msTicks++;
}

// Delays number of tick Systicks (happens every 1 ms)
void Delay_ms(uint32_t ms) {
    uint32_t curTicks;
    curTicks = msTicks;
    while ((msTicks - curTicks) < ms);
}

// Delays in microseconds using timer 3.
void Delay_us(uint32_t us) {
    uint32_t cur_us = _timers[3]->TC;
    while ((_timers[3]->TC - cur_us) < us);
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
