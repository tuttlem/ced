
#ifndef __ced_cont_stack_h__
#define __ced_cont_stack_h__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "list.h"
#include "data_cmp.h"

#define ced_stack_size(stack) (stack->list->size)

typedef struct {
    CED_REFLECT_INFO

    ced_list_p list;
} ced_stack_t, *ced_stack_p;

/**
 * @brief Stack iteration macro
 * @param iter The iterator variable
 * @param stack The stack to iterate over
 */
#define ced_stack_foreach(iter, stack) \
   for (iter = stack->list->head; iter != NULL; iter = iter->next)

/**
 * @brief Creates a new stack
 * @return A pointer to the new stack
 */
ced_stack_p ced_stack_new();

/**
 * @brief Frees a stack
 * @param stack The stack to free
 */
void ced_stack_free(ced_stack_p stack);

/**
 * @brief Creates a new stack node
 * @return A pointer to the new stack node
 */
void ced_stack_push(ced_stack_p stack, void *data);

/**
 * @brief Frees a stack node
 * @param node The stack node to free
 */
void *ced_stack_pop(ced_stack_p stack);

/**
 * @brief Peeks at the top of the stack
 * @param stack The stack to peek at
 * @return The data at the top of the stack
 */
void *ced_stack_peek(ced_stack_p stack);


#endif /* __ced_cont_stack_h__ */