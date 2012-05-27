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

#include "hash.h"
#include <stdlib.h>

// A node in the hash table
typedef struct _hash_node_t {
    Hash_Key_t key;
    uint16_t state;
    void *data;
} hash_node_t;

// The hash table itself.
struct _hash_t {
    uint16_t size;        // number of allocated elements
    uint16_t active;      // number of active elements
    hash_node_t *table;
    Hash_Destroy_t destroy;
};

struct _hash_iter_t {
    uint32_t index;
    struct _hash_t *hash;
};

// State and initialization constants
enum hash_constants {
    HASH_EMPTY, HASH_ACTIVE, HASH_DELETED,
    HASH_INI = 7
};

struct _hash_t *Hash_Init(Hash_Destroy_t destroy) {
    struct _hash_t *h = malloc(sizeof(struct _hash_t));
    if (h == NULL) return NULL;

    h->size = HASH_INI;
    h->table = calloc(h->size, sizeof(hash_node_t));
    if (h->table == NULL) {
        free(h);
        return NULL;
    }

    h->active = 0;
    h->destroy = destroy;

    return h;
}

static size_t hash(Hash_Key_t k) {
    return k;
}

static int hash_resize(struct _hash_t *h, size_t new_size) {
    hash_node_t *new = calloc(new_size, sizeof(hash_node_t));
    if (new == NULL) return HASH_ERROR;

    // iterate over the old table
    size_t i, pos;
    for (i = 0; i < h->size; i++) {
        if (h->table[i].state == HASH_ACTIVE) {
            // get the location in the new table
            pos = hash(h->table[i].key) % new_size;
            while (new[pos].state != HASH_EMPTY) {
                pos = (pos + 1) % new_size;
            }
            // copy it to the new table
            new[pos].state = HASH_ACTIVE;
            new[pos].key = h->table[i].key;
            new[pos].data = h->table[i].data;
        }
    }
    // delete the old table, and update the structure
    free(h->table);
    h->table = new;
    h->size = new_size;
    return HASH_OK;
}

// Check if a resize is needed.
// This hash grows slowly on purpose, not to eat too much memory.
static inline uint8_t check_resize(struct _hash_t *h) {
    uint8_t state = HASH_OK;
    if ((h->size * 2 / 3) <= (h->active + 1)) {
        state = hash_resize(h, h->size + HASH_INI);
    }
    return state;
}

uint8_t Hash_Set(struct _hash_t *h, const Hash_Key_t k, void *v) {
    uint8_t state = check_resize(h);
    if (state == HASH_ERROR) return state;

    // Get the position in the hash
    size_t pos = hash(k) % h->size;
    while ((h->table[pos].state != HASH_EMPTY)
            && (h->table[pos].key != k)) {
        pos = (pos + 1) % h->size;
    }

    // Data is updated
    if (h->table[pos].state != HASH_ACTIVE) {
        h->table[pos].key = k;
        h->table[pos].state = HASH_ACTIVE;
        h->active++;
    } else if (h->destroy != NULL) {
        h->destroy(h->table[pos].data);
    }
    h->table[pos].data = v;

    return HASH_OK;
}

void *Hash_Get(struct _hash_t *h, const Hash_Key_t k) {
    // Get the position of k in the hash
    size_t pos = hash(k) % h->size;
    while ((h->table[pos].state != HASH_EMPTY) &&
            (h->table[pos].key != k)) {
        pos = (pos + 1) % h->size;
    }
    if ((h->table[pos].key != k) ||
            (h->table[pos].state != HASH_ACTIVE)) {
        return NULL;
    }
    // Returns the value
    return h->table[pos].data;
}

size_t Hash_Len(struct _hash_t *h) {
    return h->active;
}

void Hash_Destroy(struct _hash_t *h) {
    size_t i;
    if (h->destroy != NULL) {
        for (i = 0; i < h->size; i++) {
            if (h->table[i].state == HASH_ACTIVE) {
                h->destroy(h->table[i].data);
            }
        }
    }
    free(h->table);
    free(h);
}

static inline uint16_t _iter_move_index(uint16_t index, struct _hash_t *hash) {
    while ((index < hash->size)
            && (hash->table[index].state != HASH_ACTIVE)) {
        index ++;
    }
    return index;
}

Hash_Iter_t *Hash_Iter_Init(Hash_t *hash) {
    Hash_Iter_t *iter = malloc(sizeof(Hash_Iter_t));
    iter->hash = hash;
    iter->index = _iter_move_index(0, hash);
    return iter;
}

inline int Hash_Iter_Has_Next(Hash_Iter_t *iter) {
    return iter->index < iter->hash->size;
}

Hash_Key_t Hash_Iter_Get_Next(Hash_Iter_t *iter) {
    Hash_Key_t key = iter->hash->table[iter->index].key;
    iter->index = _iter_move_index(iter->index + 1, iter->hash);
    return key;
}

inline void Hash_Iter_Destroy(Hash_Iter_t *iter) {
    free(iter);
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
