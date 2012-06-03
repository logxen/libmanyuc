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

#include <stdint.h>
#include <stdlib.h>

/** Opaque structure used for the timer. */
typedef struct _sw_timer_t SWTimer_t;

/** Opaque structure used to store scheduled tasks.  */
typedef struct _scheduled_t Scheduled_t;

/** Interrupt function prototype */
typedef void (*Timer_Int_Func)(void);

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
 * @return The slot number where the callback was stored.
 */
uint32_t SWTimer_Store(SWTimer_t *timer, Timer_Int_Func func,
                uint32_t time_delay, uint8_t repeat);

/** Increments the internal time counter.
 * @param timer An initialized software timer.
 * @param slot The slot that has to be incremented.
 */
void SWTimer_Tick(SWTimer_t *timer, uint32_t slot);

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

#ifdef PEPE

/** Stores an element in the timer table.
 * If the key is already present, the data is replaced.
 * @param timer An initialized timer table.
 * @param key A valid key for the timer table.
 * @param data The data to be stored.
 * @return HASH_OK if the value could be stored or HASH_ERROR if there was a problem.
 */
uint8_t SWTimer_Set(SWTimer_t *timer, const SWTimer_Key_t key, void *data);

/** Fetches an element from the timer table identified by the key. If
 * the key is not present returns NULL, in other cases it returns a
 * pointer to the data.
 * @param timer An initialized timer table.
 * @param key A valid key for the timer table.
 * @return The data associated to the key, or NULL when not found.
 */
void *SWTimer_Get(SWTimer_t *timer, const SWTimer_Key_t key);

/** Returns the number of elements contained in the timer table.
 * @param timer An initialized timer table.
 * @return The number of elements contained in the timer table.
 */
size_t SWTimer_Len(SWTimer_t *timer);

/** Destroys the timer table elements. Both the contents and the table
 * get destroyed.
 * @param timer An initialized timer table.
 */
void SWTimer_Destroy(SWTimer_t *timer);

/** Creates a new iterator for the timer.
 * @param timer An initialized timer table.
 * @return An initialized iterator.
 */
SWTimer_Iter_t *SWTimer_Iter_Init(SWTimer_t *timer);

/** States whether there is a next item or not.
 * @param iter An initialized timer iterator.
 * @return 0 if there isn't a next item, 1 if there is.
 */
int SWTimer_Iter_Has_Next(SWTimer_Iter_t *iter);

/** Returns the next available key in the timer. Once this function is
 * called, the current pointer will indicate the next element.
 * @param iter An initialized timer iterator.
 * @return The next key available in the iterator.
 */
SWTimer_Key_t SWTimer_Iter_Get_Next(SWTimer_Iter_t *iter);

/** Destroys the iterator. Should be called once the iterator is not
 * needed.
 * @param iter An initialized timer iterator.
 */
void SWTimer_Iter_Destroy(SWTimer_Iter_t *iter);

#endif

#endif 
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
