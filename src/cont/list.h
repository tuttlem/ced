#ifndef __ced_cont_list_h__
#define __ced_cont_list_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "types.h"

typedef struct ced_list_node_t {
    CED_REFLECT_INFO

    struct ced_list_node_t *next;
    struct ced_list_node_t *prev;

    void *data;
} ced_list_node_t, *ced_list_node_p;

typedef struct ced_list_t {
    CED_REFLECT_INFO

    ced_list_node_t *head;
    ced_list_node_t *tail;

    size_t size;
    int managed_data;
} ced_list_t, *ced_list_p;

/**
 * @brief List iteration macro
 * @param iter The iterator variable
 * @param list The list to iterate over
 */
#define ced_list_foreach(iter, list) \
   for (iter = list->head; iter != NULL; iter = iter->next)

/**
 * @brief List iteration macro (reverse)
 * @param iter The iterator variable
 * @param list The list to iterate over
 */
#define ced_list_foreach_reverse(iter, list) \
   for (iter = list->tail; iter != NULL; iter = iter->prev)

/**
 * @brief Creates a new list
 * @return A pointer to the new list
 */
ced_list_p ced_list_new();

/**
 * @brief Frees a list
 * @param list The list to free
 */
void ced_list_free(ced_list_p list);

/**
 * @brief Creates a new list node
 * @return A pointer to the new list node
 */
ced_list_node_p ced_list_node_new();

/**
 * @brief Frees a list node
 * @param node The list node to free
 * @param managed_data Whether the node's data should be freed
 */
void ced_list_node_free(ced_list_node_p node, int managed_data);

/**
 * @brief Gets a list node at a given index
 * @param list The list to get the node from
 * @param index The index of the node to get
 * @return A pointer to the node at the given index
 */
ced_list_node_p ced_list_node_get(ced_list_p list, size_t index);

/**
 * @brief Gets a list node containing the given data
 * @param list The list to search
 * @param cmp The comparator function to use
 * @param data The data to search for
 * @return A pointer to the node containing the given data
 */
ced_list_node_p ced_list_find(ced_list_p list, ced_data_cmp cmp, void *data);

/**
 * @brief Gets the data at a given index
 * @param list The list to get the data from
 * @param index The index of the data to get
 * @return A pointer to the data at the given index
 */
void* ced_list_get(ced_list_p list, size_t index);

/**
 * @brief Sets the data at a given index
 * @param list The list to set the data in
 * @param index The index of the data to set
 * @param data The data to set
 */
void ced_list_set(ced_list_p list, size_t index, void *data);

/**
 * @brief Appends data to the end of a list
 * @param list The list to append to
 * @param data The data to append
 */
void ced_list_append(ced_list_p list, void *data);

/**
 * @brief Prepends data to the beginning of a list
 * @param list The list to prepend to
 * @param data The data to prepend
 */
void ced_list_prepend(ced_list_p list, void *data);

/**
 * @brief Inserts data before a given index
 * @param list The list to insert into
 * @param index The index to insert before
 * @param data The data to insert
 */
void ced_list_insert_before(ced_list_p list, size_t index, void *data);

/**
 * @brief Inserts data after a given index
 * @param list The list to insert into
 * @param index The index to insert after
 * @param data The data to insert
 */
void ced_list_insert_after(ced_list_p list, size_t index, void *data);

/**
 * @brief Removes a node from a list
 * @param list The list to remove from
 * @param cmp The comparator function to use
 * @param data The data to remove
 */
void ced_list_remove(ced_list_p list, ced_data_cmp cmp, void *data);

/**
 * @brief Removes the first node from a list
 * @param list The list to remove from
 * @return The data from the removed node
 */
void* ced_list_remove_head(ced_list_p list);

/**
 * @brief Removes the last node from a list
 * @param list The list to remove from
 * @return The data from the removed node
 */
void* ced_list_remove_tail(ced_list_p list);

/**
 * @brief Performs a merge sort on a list and returns the result
 * @param list The list to sort
 * @param cmp The comparator function to use
 */
void ced_list_sort(ced_list_p list, ced_data_cmp cmp);

#endif /* __ced_cont_list_h__ */