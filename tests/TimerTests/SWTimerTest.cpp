/*
 * libmanyuc - Test for the software timer
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

#include "CppUTest/TestHarness.h"
#include "libmanyuc.h"
#include <stdio.h>

#define SLOTS 3

uint32_t counter;
void _inc_counter() {
	counter++;
}
uint32_t counter2;
void _inc_counter2() {
	counter2++;
}

TEST_GROUP(SWTimer_t)
{ 
	SWTimer_t *t;

	void setup()
	{
		t = SWTimer_Init(SLOTS);
		counter = 0;
 	}
	void teardown()
	{
		SWTimer_Destroy(t);
	}
};

TEST(SWTimer_t, Empty)
{
	for (int i = 0; i < SLOTS; i++) {
		CHECK_EQUAL(0, SWTimer_Get_TC(t, i));
		CHECK_EQUAL(0, SWTimer_Get_Reload(t, i));
		CHECK_EQUAL(0, SWTimer_Get_Length(t, i));
	}
}

TEST(SWTimer_t, StoreOne)
{
	uint32_t id = 99;
	uint32_t slot = SWTimer_Store(t, NULL, 100, 0, &id);
	CHECK_EQUAL(0, slot);
	CHECK_EQUAL(0, id);
	CHECK_EQUAL(0, SWTimer_Get_TC(t, slot));
	CHECK_EQUAL(1, SWTimer_Get_Length(t, slot));
	CHECK_EQUAL(100, SWTimer_Get_Reload(t, slot));
}

TEST(SWTimer_t, StoreOneEach)
{
	uint32_t slot, i;
	uint32_t id = 99;
   
	for (i = 0; i < SLOTS; i++) {
		slot = SWTimer_Store(t, NULL, (i+1) * 100, 0, &id);
		CHECK_EQUAL(i, slot);
		CHECK_EQUAL(0, id);
	}
	for (i = 0; i < SLOTS; i++) {
		CHECK_EQUAL(0, SWTimer_Get_TC(t, i));
		CHECK_EQUAL((i+1)*100, SWTimer_Get_Reload(t, i));
		CHECK_EQUAL(1, SWTimer_Get_Length(t, i));
	}
}

TEST(SWTimer_t, StoreMany)
{
	uint32_t slot, i, id = 99;
	uint32_t initial[] = { 12, 28, 75 };
	uint32_t second[]  = { 18, 14, 15 };
	uint32_t third[]   = {  9, 49, 25 };

	uint32_t gcd2[] = { 6, 14, 15 };
	uint32_t gcd3[] = { 3, 7, 5 };

	for (i = 0; i < SLOTS; i++) {
		slot = SWTimer_Store(t, NULL, initial[i], 1, &id);
		CHECK_EQUAL(i, slot);
		CHECK_EQUAL(0, id);
	}
	for (i = 0; i < SLOTS; i++) {
		slot = SWTimer_Store(t, NULL, second[i], 1, &id);
		CHECK_EQUAL(i, slot);
		CHECK_EQUAL(1, id);
		CHECK_EQUAL(0, SWTimer_Get_TC(t, i));
		CHECK_EQUAL(gcd2[i], SWTimer_Get_Reload(t, i));
		CHECK_EQUAL(2, SWTimer_Get_Length(t, i));
	}
	for (i = 0; i < SLOTS; i++) {
		slot = SWTimer_Store(t, NULL, third[i], 1, &id);
		CHECK_EQUAL(i, slot);
		CHECK_EQUAL(2, id);
		CHECK_EQUAL(0, SWTimer_Get_TC(t, i));
		CHECK_EQUAL(gcd3[i], SWTimer_Get_Reload(t, i));
		CHECK_EQUAL(3, SWTimer_Get_Length(t, i));
	}
}

TEST(SWTimer_t, TickOne)
{
	SWTimer_Store(t, NULL, 100, 0, NULL);
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(1, SWTimer_Get_TC(t, 0));
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(2, SWTimer_Get_TC(t, 0));
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(3, SWTimer_Get_TC(t, 0));
}

TEST(SWTimer_t, TickEach)
{
	uint32_t i;
   
	for (i = 0; i < SLOTS; i++) {
		SWTimer_Store(t, NULL, (i+1) * 100, 0, NULL);
	}
	for (i = 0; i < SLOTS; i++) {
		SWTimer_Tick(t, i);
		CHECK_EQUAL(1, SWTimer_Get_TC(t, i));
	}
}

TEST(SWTimer_t, CallHandler)
{
	SWTimer_Store(t, _inc_counter, 2, 1, NULL);
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(1, counter);
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(2, counter);
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(3, counter);
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(4, counter);
}

TEST(SWTimer_t, CallTwoHandlers)
{
	SWTimer_Store(t, _inc_counter, 12, 1, NULL);
	SWTimer_Store(t, NULL, 28, 1, NULL);
	SWTimer_Store(t, NULL, 45, 1, NULL);
	SWTimer_Store(t, _inc_counter2, 18, 1, NULL);

	// The gcd is 6, 2 ticks for the first counter, 
	// 3 for the second counter
	SWTimer_Tick(t, 0);
	CHECK_EQUAL(0, counter);
	CHECK_EQUAL(0, counter2);

	SWTimer_Tick(t, 0);
	CHECK_EQUAL(1, counter);
	CHECK_EQUAL(0, counter2);

	SWTimer_Tick(t, 0);
	CHECK_EQUAL(1, counter);
	CHECK_EQUAL(1, counter2);

	SWTimer_Tick(t, 0);
	CHECK_EQUAL(2, counter);
	CHECK_EQUAL(1, counter2);
}
