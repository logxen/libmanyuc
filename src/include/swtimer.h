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

#ifndef _SWTIMER_H
#define _SWTIMER_H

#include "port.h"
#include <stdint.h>
#include <stdlib.h>

/** Opaque structure used for the timer. */
typedef struct _sw_timer_t SWTimer_t;

/** Opaque structure used to store scheduled tasks.  */
typedef struct _scheduled_t Scheduled_t;

/** Initializes the software controlled timer.
 * @param slots the number of slots into which the timer should be divided.
 * @return An empty timer structure
 */
SWTimer_t *SWTimer_Init(uint32_t slots);

/** Stores a callback function in the timer.
 * @param timer An initialized software timer.
 * @param func The callback function to call when the time comes.
 * @param time_delay The amount of time to wait until the function is called
 * @param repeat Whether to keep calling or not. 0 means no repeat.
 * @param mr_id A pointer to an integer where the id of the scheduled task
 * will be stored.  If NULL is received, no information is stored.
 * @return The slot number where the callback was stored.
 */
uint32_t SWTimer_Store(SWTimer_t *timer, Int_Func func,
                uint32_t time_delay, uint8_t repeat, uint32_t *mr_id);

/** Increments the internal time counter.  The frequency of calling this
 * ticker is determined by the the Reload value of the slot.
 * @param timer An initialized software timer.
 * @param slot The slot that has to be incremented.
 */
void SWTimer_Tick(SWTimer_t *timer, uint32_t slot);

/** Increments the internal time counter by value N.  
 * Useful to call it when modifying the frequency.
 * @param timer An initialized software timer.
 * @param slot The slot that has to be incremented.
 * @param n The amount of ticks to make at the same time.
 */
void SWTimer_TickMany(SWTimer_t *timer, uint32_t slot, uint32_t n);

/** Returns the current time counter for the selected slot. 
 * @param timer An initialized software timer.
 * @param slot The slot that has to be queried.
 * @return The current time counter for that slot.
 */
uint32_t SWTimer_Get_TC(SWTimer_t *timer, uint32_t slot);

/** Returns the current reload value for the selected slot. 
 * @param timer An initialized software timer.
 * @param slot The slot that has to be queried.
 * @return The current reload value for that slot.
 */
uint32_t SWTimer_Get_Reload(SWTimer_t *timer, uint32_t slot);

/** Returns the current length of scheduled tasks for the selected slot. 
 * @param timer An initialized software timer.
 * @param slot The slot that has to be queried.
 * @return The current length of scheduled tasks for that slot.
 */
uint32_t SWTimer_Get_Length(SWTimer_t *timer, uint32_t slot);


/** Releases all the memory allocated for the software timer. 
 * @param timer An initialized software timer.
 */
void SWTimer_Destroy(SWTimer_t *timer);


#endif 
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
