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

    /** Opaque structure to hold information about a scheduled task.
     *  It should be constructed by calling Scheduler_Init.
     */
    typedef struct _scheduler_t Scheduler_t;

    /** Initializes a scheduled task and starts executing that task.
     *  @param func The task function to call.
     *  @param delay_us The delay with which to call the function, in
     *                  microseconds. The lower limit for this value is 
     *                  architecture dependent.
     *  @param repeat Whether this task should be repeated or not (1 to
     *                repeat, 0 to execute only once).
     *  @return An initialized Scheduler_t structure.
     */
    Scheduler_t Scheduler_Init_us(Int_Func func, uint32_t delay_us, uint8_t repeat);

    /** Initializes a scheduled task and starts executing that task.
     *  @param func The task function to call.
     *  @param delay The delay with which to call the function, in
     *               seconds. The lower limit for this value is 
     *               architecture dependent.
     *  @param repeat Whether this task should be repeated or not (1 to
     *                repeat, 0 to execute only once).
     *  @return An initialized Scheduler_t structure.
     */
    static inline Scheduler_t Scheduler_Init(Int_Func func, float delay,
        uint8_t repeat) {
        return Scheduler_Init_us(func, delay*1000000, repeat);
    }

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
