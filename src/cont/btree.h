
#ifndef __ced_cont_btree_h__

#define __ced_cont_btree_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "types.h"

typedef struct ced_btree_node_t {
    CED_REFLECT_INFO

    struct ced_btree_node_t *left;
    struct ced_btree_node_t *right;

    void *key;
    void *data;
} ced_btree_node_t, *ced_btree_node_p;

typedef struct ced_btree_t {
    CED_REFLECT_INFO

    ced_btree_node_p root;

    ced_data_cmp cmp;
    size_t size;
    int managed_data;
} ced_btree_t, *ced_btree_p;

/**
 * @brief Creates a new binary tree
 * @return A pointer to the new binary tree
 */
ced_btree_p ced_btree_new(ced_data_cmp cmp);

/**
 * @brief Frees a binary tree
 * @param tree The binary tree to free
 */
void ced_btree_free(ced_btree_p tree);

/**
 * @brief Creates a new binary tree node
 * @return A pointer to the new binary tree node
 */
ced_btree_node_p ced_btree_node_new();

/**
 * @brief Frees a binary tree node
 * @param node The binary tree node to free
 * @param managed_data Whether or not to free the data
 */
void ced_btree_node_free(ced_btree_node_p node, int managed_data);

/**
 * @brief Inserts data into a binary tree
 * @param tree The binary tree to insert into
 * @param key The key to insert
 * @param data The data to insert
 */
void ced_btree_insert(ced_btree_p tree, void *key, void *data);

/**
 * @brief Removes data from a binary tree
 * @param tree The binary tree to remove from
 * @param key The key to remove
 */
void ced_btree_remove(ced_btree_p tree, void *key);

/**
 * @brief Finds data in a binary tree
 * @param tree The binary tree to find in
 * @param key The key to find
 * @return A pointer to the data if found, NULL otherwise
 */
void *ced_btree_get(ced_btree_p tree, void *key);

/**
 * @brief Finds the node with the requested key
 * @param tree The binary tree to find in
 * @param key The key to find
 * @return A pointer to the data if found, NULL otherwise
 */
ced_btree_node_p ced_btree_get_node(ced_btree_p tree, void *key);

/**
 * @brief Finds the minimum data in a binary tree
 * @param tree The binary tree to find in
 * @return A pointer to the minimum data if found, NULL otherwise
 */
void *ced_btree_find_min(ced_btree_p tree);

/**
 * @brief Finds the maximum data in a binary tree
 * @param tree The binary tree to find in
 * @return A pointer to the maximum data if found, NULL otherwise
 */
void *ced_btree_find_max(ced_btree_p tree);

/**
 * @brief Finds the successor of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the successor of
 * @return A pointer to the successor data if found, NULL otherwise
 */
void *ced_btree_find_successor(ced_btree_p tree, void *key);

/**
 * @brief Finds the predecessor of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the predecessor of
 * @return A pointer to the predecessor data if found, NULL otherwise
 */
void *ced_btree_find_predecessor(ced_btree_p tree, void *key);

/**
 * @brief Finds the depth of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the depth of
 * @return The depth of the data in the binary tree
 */
size_t ced_btree_depth(ced_btree_p tree, void *key);

#endif /* __ced_cont_btree_h__ */