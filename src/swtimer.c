/*
 * A software timer implementation
 * Copyright (C) 2012 Margarita Manterola Rivero
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

#include "swtimer.h"
#include "port.h"
#include <stdlib.h>

struct _scheduled_t {
    Timer_Int_Func func;
    uint32_t expect;
    uint32_t reload;
    uint8_t active;
    uint8_t used;
};

struct _sw_timer_slot_t {
    uint32_t reload;
    uint32_t tc;
    uint32_t length;
    struct _scheduled_t* sch;
};

struct _sw_timer_t {
    uint32_t  length;
    struct _sw_timer_slot_t* slots;
};

SWTimer_t *SWTimer_Init(uint32_t slots) {
    SWTimer_t *t = malloc(sizeof(SWTimer_t));
    if (t == NULL) return NULL;

    t->length = slots;
    t->slots = calloc(slots, sizeof(struct _sw_timer_slot_t));

    if (t->slots == NULL) {
        free(t);
        return NULL;
    }

    return t;
}

static inline uint32_t _find_best_slot(SWTimer_t *timer, 
        uint32_t time_delay) {

    int32_t best = -1, shortest = 0;
    uint32_t i;
    for (i = 0; i < timer->length; i++) {
        // If there's an empty slot, return it immediately
        if (timer->slots[i].reload == 0) {
            return i;
        }
        // Find the best that shares a common divisor
        if (time_delay % timer->slots[i].reload == 0) {
            if ( (best < 0) || (timer->slots[i].reload > timer->slots[best].reload)) {
                best = i;
            }
        }
        // If no common divisor, find shortest
        if (timer->slots[i].length < timer->slots[shortest].length) {
            shortest = i;
        }
    }
    if (best >= 0) {
        return best;
    }
    return shortest;
}

static inline uint32_t _add_sch(SWTimer_t *timer, uint32_t slot) {
    uint32_t amount = timer->slots[slot].length + 1;
    timer->slots[slot].sch = realloc(timer->slots[slot].sch, 
            amount * sizeof(struct _scheduled_t));
    if (timer->slots[slot].sch == NULL) Show_Error();
    timer->slots[slot].length = amount;
    return amount - 1;
}

static inline uint32_t _gcd(uint32_t a, uint32_t b) {
    if (a == 0) return b;
    uint32_t r = b % a;
    while (r != 0) {
        b = a;
        a = r;
        r = b % a;
    }
    return a;
}

static inline void _sch_store (struct _scheduled_t *sch, Timer_Int_Func func,
    uint32_t time_delay, uint32_t tc, uint8_t repeat) {
    sch->func = func;
    sch->active = 1;
    sch->used = 1;
    sch->reload = repeat ? time_delay : 0;
    sch->expect = time_delay + tc;
}


uint32_t SWTimer_Store(SWTimer_t *timer, Timer_Int_Func func,
            uint32_t time_delay, uint8_t repeat) {

    if (time_delay == 0) Show_Error();

    uint32_t slot = _find_best_slot(timer, time_delay);
    uint32_t id = _add_sch(timer, slot);

    if (id == 0) {
        timer->slots[slot].reload = time_delay;
    } else {
        // Find new gcd
        uint32_t old = timer->slots[slot].reload;
        uint32_t gcd = _gcd(old, time_delay);

        // Store updated values
        if (gcd != old) {
            uint32_t factor = old / gcd;
            timer->slots[slot].reload = gcd;
            timer->slots[slot].tc *= factor;
            uint32_t i;
            for (i = 0; i < (timer->slots[slot].length-1); i++) {
                timer->slots[slot].sch[i].reload *= factor;
                timer->slots[slot].sch[i].expect *= factor;
            }
        }
    }

    // Store this function
    time_delay = time_delay / timer->slots[slot].reload;
    _sch_store(&(timer->slots[slot].sch[id]), func, time_delay, 
        timer->slots[slot].tc, repeat);
    return slot;
}

static inline void _handle_interrupt(SWTimer_t *timer, uint32_t slot, uint32_t id) {
    if (timer->slots[slot].sch[id].func) {
        timer->slots[slot].sch[id].func();
    }
    if (timer->slots[slot].sch[id].reload) {
        timer->slots[slot].sch[id].expect = timer->slots[slot].tc + 
            timer->slots[slot].sch[id].reload;
    }
}

void SWTimer_Tick(SWTimer_t *timer, uint32_t slot) {
    timer->slots[slot].tc++;
    uint32_t i;
    for (i = 0; i < timer->slots[slot].length; i++) {
        if (timer->slots[slot].tc == timer->slots[slot].sch[i].expect) {
            _handle_interrupt(timer, slot, i);
        }
    }
}

uint32_t SWTimer_Get_TC(SWTimer_t *timer, uint32_t slot) {
    return timer->slots[slot].tc;
}

uint32_t SWTimer_Get_Reload(SWTimer_t *timer, uint32_t slot) {
    return timer->slots[slot].reload;
}

uint32_t SWTimer_Get_Length(SWTimer_t *timer, uint32_t slot) {
    return timer->slots[slot].length;
}

void SWTimer_Destroy(SWTimer_t *timer) {
    uint32_t i;
    for (i = 0; i < timer->length; i++) {
        free(timer->slots[i].sch);
    }
    free(timer->slots);
    free(timer);
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
