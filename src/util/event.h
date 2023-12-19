#ifndef __ced_util_event_h__
#define __ced_util_event_h__

#include "../defs.h"
#include "../reflect.h"
#include "../cont/list.h"
#include "../cont/htable.h"

/**
 * @brief A function that handles an event
 */
typedef void (*ced_event_handler)(void *source, void *info);

/**
 * @brief A table of events
 */
typedef struct ced_event_table_t {
    CED_REFLECT_INFO

    ced_htable_p slots;
} ced_event_table_t, *ced_event_table_p;

/**
 * @brief A slot within an event table
 */
typedef struct ced_event_slot_t {
    CED_REFLECT_INFO

    ced_list_p handlers;
} ced_event_slot_t, *ced_event_slot_p;

/**
 * @brief Creates a new event table
 * @return A pointer to the new event table
 */
ced_event_table_p ced_event_table_new();

/**
 * @brief Frees an event table
 * @param table The event table to free
 */
void ced_event_table_free(ced_event_table_p table);

/**
 * @brief Adds a slot to an event table
 * @param table The event table to add to
 * @param name The name of the slot
 * @return The index of the slot
 */
int ced_event_table_add_slot(ced_event_table_p table, const char *name);

/**
 * @brief Adds a handler to a slot in an event table
 * @param table The event table to add to
 * @param slot_name The name of the slot
 * @param handler The handler to add
 * @return The index of the handler
 */
int ced_event_table_add_handler(ced_event_table_p table, const char *slot_name, ced_event_handler handler);

/**
 * @brief Removes a handler from a slot in an event table
 * @param table The event table to remove from
 * @param slot_name The name of the slot
 * @param handler The handler to remove
 * @return The index of the handler
 */
int ced_event_table_remove_handler(ced_event_table_p table, const char *slot_name, ced_event_handler handler);

/**
 * @brief Raises an event
 * @param table The event table to raise the event on
 * @param slot_name The name of the slot to raise the event on
 * @param source The source of the event
 * @param info The info of the event
 */
void ced_event_table_raise(ced_event_table_p table, const char *slot_name, void *source, void *info);

#endif /* __ced_util_event_h__ */