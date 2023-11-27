#include "queue.h"

/**
 * @brief Creates a new queue
 * @return A pointer to the new queue
 */
ced_queue_p ced_queue_new() {
    ced_queue_p queue = malloc(sizeof(ced_queue_t));
    assert(queue != NULL);

    ced_reflect_set_info(queue, reflect_type_queue);
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->managed_data = 0;

    return queue;
}

/**
 * @brief Frees a queue
 * @param queue The queue to free
 */
void ced_queue_free(ced_queue_p queue) {
    ced_queue_node_p node, next;

    for (node = queue->head; node != NULL; node = next) {
        if (queue->managed_data) {
            free(node->data);
        }

        next = node->next;
        free(node);
    }

    free(queue);
}

/**
 * @brief Creates a new queue node
 * @return A pointer to the new queue node
 */
ced_queue_node_p ced_queue_node_new() {
    ced_queue_node_p node = malloc(sizeof(ced_queue_node_t));
    assert(node != NULL);

    ced_reflect_set_info(node, reflect_type_queue_node);
    node->data = NULL;
    node->next = NULL;

    return node;
}

/**
 * @brief Frees a queue node
 * @param node The queue node to free
 */
void ced_queue_node_free(ced_queue_node_p node) {
    assert(node != NULL);
    free(node);
}

/**
 * @brief Enqueues data
 * @param queue The queue to enqueue to
 * @param data The data to enqueue
 */
void ced_queue_enqueue(ced_queue_p queue, void *data) {
    ced_queue_node_p node = ced_queue_node_new();
    node->data = data;

    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->size++;
}

/**
 * @brief Dequeues data
 * @param queue The queue to dequeue from
 * @return The data dequeued
 */
void *ced_queue_dequeue(ced_queue_p queue) {
    ced_queue_node_p node = queue->head;
    void *data;

    if (node == NULL) {
        return NULL;
    }

    queue->head = node->next;
    queue->size--;

    data = node->data;
    ced_queue_node_free(node);

    return data;
}

/**
 * @brief Peeks at the front of the queue
 * @param queue The queue to peek at
 * @return The data at the front of the queue
 */
void *ced_queue_peek(ced_queue_p queue) {
    if (queue->head == NULL) {
        return NULL;
    }

    return queue->head->data;
}

