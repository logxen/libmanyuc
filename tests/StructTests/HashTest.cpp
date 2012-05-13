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

TEST(Hash_t, HashIterator_Empty)
{
	Hash_Iter_t *iter = Hash_Iter_Init(h);
	CHECK_FALSE(Hash_Iter_Has_Next(iter));
	Hash_Iter_Destroy(iter);
}

TEST(Hash_t, HashIterator_OneItem)
{
	Hash_Set(h, 1, data);
	Hash_Iter_t *iter = Hash_Iter_Init(h);
	CHECK(Hash_Iter_Has_Next(iter));
	Hash_Iter_Destroy(iter);
}

TEST(Hash_t, HashIterator_ReplaceItem)
{
	Hash_Set(h, 1, data);
	Hash_Set(h, 1, data+1);
	Hash_Iter_t *iter = Hash_Iter_Init(h);
	CHECK(Hash_Iter_Has_Next(iter));
	Hash_Iter_Destroy(iter);
}

TEST(Hash_t, HashIterator_GetItem) {
	Hash_Set(h, 125, data);
	Hash_Iter_t *iter = Hash_Iter_Init(h);
	CHECK_EQUAL(125, Hash_Iter_Get_Next(iter));
	CHECK_FALSE(Hash_Iter_Has_Next(iter));
	Hash_Iter_Destroy(iter);
}

TEST(Hash_t, HashIterator_GetTwoItems) {
	Hash_Set(h, 125, data);
	Hash_Set(h, 126, data+1);
	Hash_Iter_t *iter = Hash_Iter_Init(h);
	CHECK_EQUAL(125, Hash_Iter_Get_Next(iter));
	CHECK(Hash_Iter_Has_Next(iter));
	CHECK_EQUAL(126, Hash_Iter_Get_Next(iter));
	CHECK_FALSE(Hash_Iter_Has_Next(iter));
	Hash_Iter_Destroy(iter);
}

TEST_GROUP(Hash_With_Destroy)
{ 
	Hash_t *h;
	int *data1;
	int *data2;

	void setup()
	{
		h = Hash_Init(cpputest_free);
		data1 = (int*) malloc(sizeof(int));
		data2 = (int*) malloc(sizeof(int));
 	}
	void teardown()
	{
		Hash_Destroy(h);
	}
};

TEST(Hash_With_Destroy, ReplaceItem)
{
	CHECK_EQUAL(Hash_Set(h, 1, data1), HASH_OK);
	CHECK_EQUAL(Hash_Set(h, 1, data2), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), (void*) (data2));
	CHECK_EQUAL(Hash_Len(h), 1);
}

TEST(Hash_With_Destroy, TwoItems)
{
	CHECK_EQUAL(Hash_Set(h, 1, data1), HASH_OK);
	CHECK_EQUAL(Hash_Set(h, 2, data2), HASH_OK);
	CHECK_EQUAL(Hash_Get(h, 1), (void*) data1);
	CHECK_EQUAL(Hash_Get(h, 2), (void*) (data2));
	CHECK_EQUAL(Hash_Len(h), 2);
}
