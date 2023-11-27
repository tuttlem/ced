
#include "stack.h"

/**
 * @brief Creates a new stack
 * @return A pointer to the new stack
 */
ced_stack_p ced_stack_new() {
    ced_stack_p stack = malloc(sizeof(ced_stack_t));
    assert(stack != NULL);

    ced_reflect_set_info(stack, reflect_type_stack);
    stack->head = NULL;
    stack->size = 0;
    stack->managed_data = 0;

    return stack;
}

/**
 * @brief Frees a stack
 * @param stack The stack to free
 */
void ced_stack_free(ced_stack_p stack) {
    ced_stack_node_p node, next;

    for (node = stack->head; node != NULL; node = next) {
        if (stack->managed_data) {
            free(node->data);
        }

        next = node->next;
        free(node);
    }

    free(stack);
}

/**
 * @brief Creates a new stack node
 * @return A pointer to the new stack node
 */
void ced_stack_push(ced_stack_p stack, void *data) {
    ced_stack_node_p node = malloc(sizeof(ced_stack_node_t));
    assert(node != NULL);

    ced_reflect_set_info(node, reflect_type_stack_node);
    node->data = data;
    node->next = stack->head;

    stack->head = node;
    stack->size++;
}

/**
 * @brief Frees a stack node
 * @param node The stack node to free
 */
void *ced_stack_pop(ced_stack_p stack) {
    ced_stack_node_p node = stack->head;
    void *data;

    if (node == NULL) {
        return NULL;
    }

    stack->head = node->next;
    stack->size--;

    data = node->data;
    free(node);

    return data;
}

/**
 * @brief Peeks at the top of the stack
 * @param stack The stack to peek at
 * @return The data at the top of the stack
 */
void *ced_stack_peek(ced_stack_p stack) {
    if (stack->head == NULL) {
        return NULL;
    }

    return stack->head->data;
}
