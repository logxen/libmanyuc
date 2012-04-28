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

TEST_GROUP(Pin)
{ 
	Pin *leds;
	void setup()
	{
		leds = (Pin*) malloc(4*sizeof(Pin));
 		leds[0] = Pin(LED1, Output);
 		leds[1] = Pin(LED2, Output);
 		leds[2] = Pin(LED3, Output);
 		leds[3] = Pin(LED4, Output);
 	}
	void teardown()
	{
		free(leds);
	}
};

TEST(Pin, Pin_On)
{
	leds[0] = 1;	
	CHECK_EQUAL(leds[0], 1);
}

TEST(Pin, Pin_Off)
{
	leds[0] = 1;
	leds[0] = 0;	
	CHECK_EQUAL(leds[0], 0);
}

