/*
 * A closed hash implementation 
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

#ifndef _HASH_H
#define _HASH_H       

#include <stdint.h>

typedef uint32_t Hash_Key_t;

typedef void (*Hash_Destroy_t)(void**); 

typedef struct _hash_t Hash_t;

/* Initializes a hash table.
 * @param destroy_function The function to destroy the data in the hash.
 * @return An initialized hash table.
 */
Hash_t *Hash_Init(Hash_Destroy_t destroy_function);

/* Stores an element in the hash table. 
 * If the key is already present, the data is replaced.
 * @param hash An initialized hash table.
 * @param key A valid key for the hash table.
 * @param data The data to be stored.
 */
uint8_t Hash_Set(Hash_t* hash, const Hash_Key_t key, void * data);

/* Fetchs an element from the hash table identified by the key. If the key
 * is not present returns NULL, in other cases it returns a pointer to the
 * data.
 * @param hash An initialized hash table.
 * @param key A valid key for the hash table.
 * @return The data associated to the key, or NULL when not found.
 */
void *Hash_Get(Hash_t*, const Hash_Key_t);

/* Returns the number of elements contained in the hash table.
 * @param hash An initialized hash table.
 * @return The number of elements contained in the hash table.
 */
size_t Hash_Len(Hash_t*);

/* Destroys the hash table elements. Both the contents and the table get
 * destroyed.
 * @param hash An initialized hash table.
 */
void Hash_Destroy(Hash_t*);

#endif // _HASH_H
