#ifndef __ced_cont_htable_h__
#define __ced_cont_htable_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "btree.h"
#include "../util/hash.h"

typedef struct ced_htable_node_t {
    CED_REFLECT_INFO

    char *key;
    void *value;
} ced_htable_node_t, *ced_htable_node_p;

typedef struct ced_htable_t {
    CED_REFLECT_INFO

    ced_btree_p buckets;
    int managed_data;
} ced_htable_t, *ced_htable_p;

/**
 * @brief Creates a new hash table
 * @return A pointer to the new hash table
 */
ced_htable_p ced_htable_new();

/**
 * @brief Frees a hash table
 * @param htable The hash table to free
 */
void ced_htable_free(ced_htable_p htable);

/**
 * @brief Inserts a key-value pair into a hash table
 * @param htable The hash table to insert into
 * @param key The key to insert
 * @param value The value to insert
 */
void ced_htable_insert(ced_htable_p htable, char *key, void *value);

/**
 * @brief Gets a value from a hash table
 * @param htable The hash table to get from
 * @param key The key to get
 * @return The value associated with the key. If the key isn't found, NULL is returned
 */
void *ced_htable_get(ced_htable_p htable, char *key);

/**
 * @brief Removes a key-value pair from a hash table
 * @param htable The hash table to remove from
 * @param key The key to remove
 */
void ced_htable_remove(ced_htable_p htable, char *key);

/**
 * @brief Checks if a hash table contains a key
 * @param htable The hash table to check
 * @param key The key to check for
 * @return 1 if the hash table contains the key, 0 otherwise
 */
int ced_htable_contains(ced_htable_p htable, char *key);


#endif /* __ced_cont_htable_h__ */