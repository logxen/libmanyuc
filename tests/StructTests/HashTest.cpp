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

TEST_GROUP(Hash_t)
{ 
	Hash_t *h;
	int *data;
	int amount;

	void setup()
	{
		amount = 30;
		h = Hash_Init(NULL);
		data = (int*) malloc(amount*sizeof(int));
 	}
	void teardown()
	{
		Hash_Destroy(h);
		free(data);
	}
};

TEST(Hash_t, Empty)
{
	CHECK_EQUAL(Hash_Get(h, 1), NULL);
	CHECK_EQUAL(Hash_Len(h), 0);
}

TEST(Hash_t, OneItem)
{
	CHECK_EQUAL(Hash_Set(h, 1, data), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), data);
	CHECK_EQUAL(Hash_Len(h), 1);
}

TEST(Hash_t, TwoItems)
{
	CHECK_EQUAL(Hash_Set(h, 1, data), HASH_OK);
	CHECK_EQUAL(Hash_Set(h, 2, data+1), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), (void*) data);
	CHECK_EQUAL(Hash_Get(h, 2), (void*) (data+1));
	CHECK_EQUAL(Hash_Len(h), 2);
}

TEST(Hash_t, ReplaceItem)
{
	CHECK_EQUAL(Hash_Set(h, 1, data), HASH_OK);
	CHECK_EQUAL(Hash_Set(h, 1, data+1), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), (void*) (data+1));
	CHECK_EQUAL(Hash_Len(h), 1);
}

TEST(Hash_t, ManyItems)
{
	for (int i=0; i<amount; i++) {
		CHECK_EQUAL(Hash_Set(h, i, data+i), HASH_OK);
	}
	for (int i=0; i<amount; i++) {
		CHECK_EQUAL(Hash_Get(h, i), (void*) (data+i));
	}
	CHECK_EQUAL(amount, Hash_Len(h));
}

TEST(Hash_t, ClashItems)
{
	CHECK_EQUAL(Hash_Set(h, 1, data), HASH_OK);
	CHECK_EQUAL(Hash_Set(h, 9, data+1), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), (void*) data);
	CHECK_EQUAL(Hash_Get(h, 9), (void*) (data+1));
	CHECK_EQUAL(Hash_Len(h), 2);
}
