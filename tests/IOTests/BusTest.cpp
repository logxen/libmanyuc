/*
 * libmanyuc - Test for Pin class
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

TEST_GROUP(Bus_t)
{ 
	Bus_t bus;
	Pin_t leds[4];

	void setup()
	{
		bus = Bus_Get(4, LED1, LED2, LED3, LED4);
		leds[0] = Pin_Get(LED1);
		leds[1] = Pin_Get(LED2);
		leds[2] = Pin_Get(LED3);
		leds[3] = Pin_Get(LED4);

 	}
	void teardown()
	{
	}
};

TEST(Bus_t, PinBus_Output)
{
	Bus_Output(bus);
	CHECK_EQUAL(GIO->PORT[1].IODIR, 
		(1 << (LED1 % 32)) | (1 << (LED2 % 32)) |
		(1 << (LED3 % 32)) | (1 << (LED4 % 32)) );
}

TEST(Bus_t, Bus_Write)
{
	Bus_Write(bus, 0b1010);
	CHECK_EQUAL(Pin_Read(leds[0]), 0);
	CHECK_EQUAL(Pin_Read(leds[1]), 1);
	CHECK_EQUAL(Pin_Read(leds[2]), 0);
	CHECK_EQUAL(Pin_Read(leds[3]), 1);
}

TEST(Bus_t, Bus_Read)
{
	Bus_Write(bus, 10);
	uint32_t data = Bus_Read(bus);
	CHECK_EQUAL(10, data);
}

