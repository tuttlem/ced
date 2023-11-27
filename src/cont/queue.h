
#ifndef __ced_cont_queue_h__
#define __ced_cont_queue_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "types.h"
#include "list.h"

#define ced_queue_size(queue) (queue->list->size)

typedef struct {
    CED_REFLECT_INFO

    ced_list_t *list;
} ced_queue_t, *ced_queue_p;

/**
 * @brief Queue iteration macro
 * @param iter The iterator variable
 * @param queue The queue to iterate over
 */
#define ced_queue_foreach(iter, queue) \
   for (iter = queue->list->head; iter != NULL; iter = iter->next)

/**
 * @brief Creates a new queue
 * @return A pointer to the new queue
 */
ced_queue_p ced_queue_new();

/**
 * @brief Frees a queue
 * @param queue The queue to free
 */
void ced_queue_free(ced_queue_p queue);

/**
 * @brief Enqueues data
 * @param queue The queue to enqueue to
 * @param data The data to enqueue
 */
void ced_queue_enqueue(ced_queue_p queue, void *data);

/**
 * @brief Dequeues data
 * @param queue The queue to dequeue from
 * @return The data dequeued
 */
void *ced_queue_dequeue(ced_queue_p queue);

/**
 * @brief Peeks at the front of the queue
 * @param queue The queue to peek at
 * @return The data at the front of the queue
 */
void *ced_queue_peek(ced_queue_p queue);

#endif