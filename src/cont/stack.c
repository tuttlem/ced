
#include "stack.h"

/**
 * @brief Creates a new stack
 * @return A pointer to the new stack
 */
ced_stack_p ced_stack_new() {
    ced_stack_p stack = malloc(sizeof(ced_stack_t));
    assert(stack != NULL);

    ced_reflect_set_info(stack, reflect_type_stack);
    stack->list = ced_list_new();

    return stack;
}

/**
 * @brief Frees a stack
 * @param stack The stack to free
 */
void ced_stack_free(ced_stack_p stack) {
    assert(stack != NULL);

    ced_list_free(stack->list);
    stack->list = NULL;

    free(stack);
}

/**
 * @brief Creates a new stack node
 * @return A pointer to the new stack node
 */
void ced_stack_push(ced_stack_p stack, void *data) {
    assert(stack != NULL);
    ced_list_prepend(stack->list, data);
}

/**
 * @brief Frees a stack node
 * @param node The stack node to free
 */
void *ced_stack_pop(ced_stack_p stack) {
    assert(stack != NULL);
    return ced_list_remove_head(stack->list);
}

/**
 * @brief Peeks at the top of the stack
 * @param stack The stack to peek at
 * @return The data at the top of the stack
 */
void *ced_stack_peek(ced_stack_p stack) {
    assert(stack != NULL);

    if (ced_stack_size(stack) == 0) {
        return NULL;
    }

    return stack->list->head->data;
}
