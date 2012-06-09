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

#include <stdint.h>
#include "port.h"
#include "board.h"

    typedef struct _scheduler_t Scheduler_t;

    Scheduler_t Scheduler_Init(Int_Func func, uint32_t time_delay, uint8_t repeat);

    void Delay(uint32_t dlyTicks);
    void Delay_us(uint32_t dlyTicks);

    /** Does nothing, for the amount of microseconds specified. 
     *  @param us amount of microseconds to wait.
     */
    void Delay_us(uint32_t us);

    /** Does nothing, for the amount of milliseconds specified. 
     *  @param ms amount of milliseconds to wait.
     */
    void Delay_ms(uint32_t ms);

    /** Does nothing, for the amount of seconds specified. 
     *  @param s amount of seconds to wait.
     */
    static inline void Delay(float s) {
        Delay_ms(s * 1000);
    }

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
