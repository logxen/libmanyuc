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
#include <stdlib.h>

/** The key used to index the hash table */
typedef uint16_t Hash_Key_t;

/** A function passed to the hash to destroy elements */
typedef void (*Hash_Destroy_t)(void *);

/** Opaque structure used to save the hash table.
 *  This is a very simple hash table, with no possibility of
 *  removing elements.  It grows slowly in order to not use
 *  that much memory.  It stores opaque pointers.
 */
typedef struct _hash_t Hash_t;

/** Opaque structure used to iterate the hash table.
 *  Should be constructed using Hash_Iter_Init.
 */
typedef struct _hash_iter_t Hash_Iter_t;

/** Result codes returned by Hash_Set */
enum { HASH_OK, HASH_ERROR };

/** Initializes a hash table.
 * @param destroy_function The function to destroy the data in the hash.
 * @return An initialized hash table.
 */
Hash_t *Hash_Init(Hash_Destroy_t destroy_function);

/** Stores an element in the hash table.
 * If the key is already present, the data is replaced.
 * @param hash An initialized hash table.
 * @param key A valid key for the hash table.
 * @param data The data to be stored.
 * @return HASH_OK if the value could be stored or HASH_ERROR if there was a problem.
 */
uint8_t Hash_Set(Hash_t *hash, const Hash_Key_t key, void *data);

/** Fetches an element from the hash table identified by the key. If
 * the key is not present returns NULL, in other cases it returns a
 * pointer to the data.
 * @param hash An initialized hash table.
 * @param key A valid key for the hash table.
 * @return The data associated to the key, or NULL when not found.
 */
void *Hash_Get(Hash_t *hash, const Hash_Key_t key);

/** Returns the number of elements contained in the hash table.
 * @param hash An initialized hash table.
 * @return The number of elements contained in the hash table.
 */
size_t Hash_Len(Hash_t *hash);

/** Destroys the hash table elements. Both the contents and the table
 * get destroyed.
 * @param hash An initialized hash table.
 */
void Hash_Destroy(Hash_t *hash);

/** Creates a new iterator for the hash.
 * @param hash An initialized hash table.
 * @return An initialized iterator.
 */
Hash_Iter_t *Hash_Iter_Init(Hash_t *hash);

/** States whether there is a next item or not.
 * @param iter An initialized hash iterator.
 * @return 0 if there isn't a next item, 1 if there is.
 */
int Hash_Iter_Has_Next(Hash_Iter_t *iter);

/** Returns the next available key in the hash. Once this function is
 * called, the current pointer will indicate the next element.
 * @param iter An initialized hash iterator.
 * @return The next key available in the iterator.
 */
Hash_Key_t Hash_Iter_Get_Next(Hash_Iter_t *iter);

/** Destroys the iterator. Should be called once the iterator is not
 * needed.
 * @param iter An initialized hash iterator.
 */
void Hash_Iter_Destroy(Hash_Iter_t *iter);


#endif // _HASH_H
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
