#include "queue.h"

/**
 * @brief Creates a new queue
 * @return A pointer to the new queue
 */
ced_queue_p ced_queue_new() {
    ced_queue_p queue = malloc(sizeof(ced_queue_t));
    assert(queue != NULL);

    ced_reflect_set_info(queue, reflect_type_queue);
    queue->list = ced_list_new();

    return queue;
}

/**
 * @brief Frees a queue
 * @param queue The queue to free
 */
void ced_queue_free(ced_queue_p queue) {
    assert(queue != NULL);

    ced_list_free(queue->list);
    queue->list = NULL;

    free(queue);
}

/**
 * @brief Enqueues data
 * @param queue The queue to enqueue to
 * @param data The data to enqueue
 */
void ced_queue_enqueue(ced_queue_p queue, void *data) {
    assert(queue != NULL);
    ced_list_append(queue->list, data);
}

/**
 * @brief Dequeues data
 * @param queue The queue to dequeue from
 * @return The data dequeued
 */
void *ced_queue_dequeue(ced_queue_p queue) {
    assert(queue != NULL);
    return ced_list_remove_head(queue->list);
}

/**
 * @brief Peeks at the front of the queue
 * @param queue The queue to peek at
 * @return The data at the front of the queue
 */
void *ced_queue_peek(ced_queue_p queue) {
    assert(queue != NULL);

    if (ced_queue_size(queue) == 0) {
        return NULL;
    }

    return queue->list->tail->data;
}

