#include "event.h"

/**
 * @brief Creates a new event table
 * @return A pointer to the new event table
 */
ced_event_table_p ced_event_table_new() {
    ced_event_table_p table = malloc(sizeof(ced_event_table_t));

    if (table == NULL) {
        return NULL;
    }

    ced_reflect_set_info(table, reflect_type_event_table);

    table->slots = ced_htable_new();
    table->slots->managed_data = 1;

    if (table->slots == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

/**
 * @brief Frees an event table
 * @param table The event table to free
 */
void ced_event_table_free(ced_event_table_p table) {
    if (table == NULL) {
        return;
    }

    // go through all of the slots and deallocate each of them
    ced_list_node_p node;
    ced_list_foreach(node, table->slots->keys) {
        char *slot_key = node->data;
        ced_event_slot_p slot = (ced_event_slot_p)ced_htable_get(table->slots, slot_key);
        ced_list_free(slot->handlers);
        free(slot);
    }

    if (table->slots != NULL) {
        ced_htable_free(table->slots);
    }

    free(table);
}

/**
 * @brief Adds a slot to an event table
 * @param table The event table to add to
 * @param name The name of the slot
 * @return The index of the slot
 */
int ced_event_table_add_slot(ced_event_table_p table, const char *name) {
    if (table == NULL || name == NULL) {
        return 0;
    }

    ced_event_slot_p slot = malloc(sizeof(ced_event_slot_t));

    if (slot == NULL) {
        return 0;
    }

    ced_reflect_set_info(slot, reflect_type_event_slot);

    slot->handlers = ced_list_new();

    if (slot->handlers == NULL) {
        free(slot);
        return 0;
    }

    ced_htable_insert(table->slots, name, slot);
    return 1;
}

/**
 * @brief Adds a handler to a slot in an event table
 * @param table The event table to add to
 * @param slot_name The name of the slot
 * @param handler The handler to add
 * @return The index of the handler
 */
int ced_event_table_add_handler(ced_event_table_p table, const char *slot_name, ced_event_handler handler) {
    if (table == NULL || slot_name == NULL || handler == NULL) {
        return 0;
    }

    ced_event_slot_p slot = (ced_event_slot_p)ced_htable_get(table->slots, slot_name);

    if (slot == NULL) {
        return 0;
    }

    ced_list_append(slot->handlers, handler);
    return 1;
}

/**
 * @brief Removes a handler from a slot in an event table
 * @param table The event table to remove from
 * @param slot_name The name of the slot
 * @param handler The handler to remove
 * @return The index of the handler
 */
int ced_event_table_remove_handler(ced_event_table_p table, const char *slot_name, ced_event_handler handler) {
    if (table == NULL || slot_name == NULL || handler == NULL) {
        return 0;
    }

    ced_event_slot_p slot = (ced_event_slot_p)ced_htable_get(table->slots, slot_name);

    if (slot == NULL) {
        return 0;
    }

    ced_list_remove(slot->handlers, NULL, handler);
    return 1;
}

/**
 * @brief Raises an event
 * @param table The event table to raise the event on
 * @param slot_name The name of the slot to raise
 * @param source The source of the event
 * @param info The info of the event
 */
void ced_event_table_raise(ced_event_table_p table, const char *slot_name, void *source, void *info) {
    if (table == NULL || slot_name == NULL) {
        return;
    }

    ced_event_slot_p slot = (ced_event_slot_p)ced_htable_get(table->slots, slot_name);

    if (slot == NULL) {
        return;
    }

    ced_list_node_p node;
    ced_list_foreach(node, slot->handlers) {
        ced_event_handler handler = node->data;
        handler(source, info);
    }
}