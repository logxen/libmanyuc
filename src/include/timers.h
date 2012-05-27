/*
 * libmanyuc - timers header file
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

#ifndef __TIMERS_H
#define __TIMERS_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef void (*timer_int_func)(void);

    typedef struct _scheduler_t Scheduler_t;

    Scheduler_t Scheduler_Init(timer_int_func func, uint32_t time_delay, uint8_t repeat);

    void wait(float s);
    void wait_ms(int ms);
    void wait_us(int us);

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
