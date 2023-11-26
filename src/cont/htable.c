#include "htable.h"

/**
 * @brief Creates a new hash table
 * @return A pointer to the new hash table
 */
ced_htable_p ced_htable_new() {
    ced_htable_p htable = malloc(sizeof(ced_htable_t));
    assert(htable != NULL);

    ced_reflect_set_info(htable, reflect_type_htable);

    htable->buckets = ced_btree_new(ced_data_cmp_int32);

    return htable;
}

/**
 * @brief Frees any allocation that the htable implementation is responsible for
 * @param node The binary tree node to free
 */
void ced_htable_node_free(ced_btree_node_p node) {
    assert(node != NULL);

    // just free the key
    ced_htable_node_p hnode = node->data;
    free(hnode->key); /* the string */
    free(node->key); /* the hash */

    if (node->left != NULL) {
        ced_htable_node_free(node->left);
    }

    if (node->right != NULL) {
        ced_htable_node_free(node->right);
    }

    free(hnode);
}

/**
 * @brief Frees a hash table
 * @param htable The hash table to free
 */
void ced_htable_free(ced_htable_p htable) {
    assert(htable != NULL);

    if (htable->buckets->root != NULL) {
        ced_htable_node_free(htable->buckets->root);
    }

    ced_btree_free(htable->buckets);
    free(htable);
}

/**
 * @brief Inserts a key-value pair into a hash table
 * @param htable The hash table to insert into
 * @param key The key to insert
 * @param value The value to insert
 */
void ced_htable_insert(ced_htable_p htable, char *key, void *value) {
    assert(htable != NULL);
    assert(key != NULL);
    assert(value != NULL);

    ced_htable_node_p node = malloc(sizeof(ced_htable_node_t));
    assert(node != NULL);
    ced_reflect_set_info(node, reflect_type_htable_node);

    uint32_t *hash = (uint32_t*)malloc(sizeof(uint32_t));
    *hash = ced_hash_fnv1a_str(key);

    node->key = strdup(key);
    node->value = value;

    ced_btree_insert(htable->buckets, hash, node);
}

/**
 * @brief Gets a value from a hash table
 * @param htable The hash table to get from
 * @param key The key to get
 * @return The value associated with the key. If the key isn't found, NULL is returned
 */
void *ced_htable_get(ced_htable_p htable, char *key) {
    assert(htable != NULL);
    assert(key != NULL);

    uint32_t hash = ced_hash_fnv1a_str(key);
    ced_htable_node_p node = (ced_htable_node_p) ced_btree_get(htable->buckets, &hash);

    if (node != NULL) {
        return node->value;
    }

    return NULL;
}

/**
 * @brief Removes a key-value pair from a hash table
 * @param htable The hash table to remove from
 * @param key The key to remove
 */
void ced_htable_remove(ced_htable_p htable, char *key) {
    assert(htable != NULL);
    assert(key != NULL);

    uint32_t hash = ced_hash_fnv1a_str(key);
    ced_btree_node_p node = ced_btree_get_node(htable->buckets, &hash);
    ced_htable_node_p hnode = (ced_htable_node_p)node->data;
    uint32_t *hash_ptr = (uint32_t*)node->key;

    if (node != NULL) {
        ced_btree_remove(htable->buckets, &hash);
        // ced_htable_node_free(node);

        if (hnode != NULL) {
            free(hnode->key); /* the string */
            free(hash_ptr); /* the hash */

            free(hnode);
        }
    }
}

/**
 * @brief Checks if a hash table contains a key
 * @param htable The hash table to check
 * @param key The key to check for
 * @return 1 if the hash table contains the key, 0 otherwise
 */
int ced_htable_contains(ced_htable_p htable, char *key) {
    assert(htable != NULL);
    assert(key != NULL);

    uint32_t hash = ced_hash_fnv1a_str(key);
    return ced_btree_get(htable->buckets, &hash) != NULL;
}
