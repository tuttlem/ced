
#include "list.h"

ced_list_p ced_list_new() {
    ced_list_p list = (ced_list_p)malloc(sizeof(ced_list_t));
    assert(list != NULL);

    list->managed_data = 0;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void ced_list_free(ced_list_p list) {
    assert(list != NULL);

    ced_list_node_p node, next;
    for (node = list->head; node != NULL; node = next) {
        next = node->next;
        ced_list_node_free(node, list->managed_data);
    }

    free(list);
}

ced_list_node_p ced_list_node_new() {
    ced_list_node_p node = (ced_list_node_p)malloc(sizeof(ced_list_node_t));
    assert(node != NULL);

    node->next = NULL;
    node->prev = NULL;
    node->data = NULL;

    return node;
}

void ced_list_node_free(ced_list_node_p node, int managed_data) {
    assert(node != NULL);

    if (node->data && managed_data) {
        free(node->data);
        node->data = NULL;
    }

    free(node);
}

ced_list_node_p ced_list_node_get(ced_list_p list, size_t index) {
    assert(list != NULL);
    assert(index < list->size);

    ced_list_node_p node;
    size_t i = 0;
    ced_list_foreach(node, list) {
        if (i == index) {
            return node;
        }

        i++;
    }

    return NULL;
}

void* ced_list_get(ced_list_p list, size_t index) {
    assert(list != NULL);
    assert(index < list->size);

    ced_list_node_p node = ced_list_node_get(list, index);
    return node->data;
}

void ced_list_set(ced_list_p list, size_t index, void *data) {
    assert(list != NULL);
    assert(index < list->size);

    ced_list_node_p node = ced_list_node_get(list, index);
    node->data = data;
}


void ced_list_append(ced_list_p list, void *data) {
    assert(list != NULL);

    ced_list_node_p node = ced_list_node_new();
    node->data = data;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }

    list->size++;
}

void ced_list_prepend(ced_list_p list, void *data) {
    assert(list != NULL);

    ced_list_node_p node = ced_list_node_new();
    node->data = data;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }

    list->size++;
}

void ced_list_insert_before(ced_list_p list, size_t index, void *data) {
    assert(list != NULL);
    assert(index < list->size);

    ced_list_node_p new_node = ced_list_node_new();
    new_node->data = data;

    if (index == 0) {
        new_node->prev = NULL;
        new_node->next = list->head;
        if (list->head != NULL) {
            list->head->prev = new_node;
        }
        list->head = new_node;
    } else {
        ced_list_node_p node = ced_list_node_get(list, index - 1);
        new_node->prev = node;
        new_node->next = node->next;
        node->next = new_node;
        if (new_node->next != NULL) {
            new_node->next->prev = new_node;
        }
    }

    list->size++;
}

void ced_list_insert_after(ced_list_p list, size_t index, void *data) {
    assert(list != NULL);
    assert(index < list->size);

    ced_list_node_p new_node = ced_list_node_new();
    new_node->data = data;

    if (index == list->size - 1) {
        ced_list_node_p last_node = ced_list_node_get(list, index);
        last_node->next = new_node;
        new_node->prev = last_node;
        new_node->next = NULL;
        list->size++;
        return;
    }

    ced_list_node_p node = ced_list_node_get(list, index);
    new_node->prev = node;
    new_node->next = node->next;
    node->next = new_node;
    new_node->next->prev = new_node;

    list->size++;
}


ced_list_node_p ced_list_find(ced_list_p list, ced_data_cmp cmp, void *data) {
    assert(list != NULL);

    ced_data_cmp _cmp = ced_data_cmp_default;

    if (cmp != NULL) {
        _cmp = cmp;
    }

    ced_list_node_p node;
    ced_list_foreach(node, list) {
        if (_cmp(node->data, data) == 0) {
            return node;
        }
    }

    return NULL;
}

void ced_list_remove(ced_list_p list, ced_data_cmp cmp, void *data) {
    assert(list != NULL);

    ced_list_node_p node = ced_list_find(list, cmp, data);
    if (node == NULL) {
        return;
    }

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    ced_list_node_free(node, list->managed_data);
    list->size--;
}

void ced_list_head(ced_list_p list, void **data, ced_list_p *rest) {
    assert(list != NULL);

    if (list->head == NULL) {
        *data = NULL;
        *rest = NULL;
        return;
    }

    *data = list->head->data;

    ced_list_p new_list = ced_list_new();
    new_list->managed_data = list->managed_data;
    new_list->size = list->size - 1;

    // re-point the new list's head to the second node
    new_list->head = list->head->next;
    new_list->tail = list->tail;

    // kill the old list's head
    ced_list_node_free(list->head, 0);

    *rest = new_list;
}

ced_list_node_p _ced_list_merge(ced_list_node_p left, ced_list_node_p right, ced_data_cmp cmp) {
    ced_list_node_p result = NULL;

    if (left == NULL) {
        return right;
    } else if (right == NULL) {
        return left;
    }

    if (cmp(left->data, right->data) <= 0) {
        result = left;
        result->next = _ced_list_merge(left->next, right, cmp);
    } else {
        result = right;
        result->next = _ced_list_merge(left, right->next, cmp);
    }

    return result;
}

void _ced_list_split(ced_list_node_p source, ced_list_node_p *left, ced_list_node_p *right) {
    ced_list_node_p fast, slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = source;
    *right = slow->next;
    slow->next = NULL;
}

void _ced_list_merge_sort(ced_list_node_p *head, ced_data_cmp cmp) {
    ced_list_node_p node = *head;
    ced_list_node_p left, right;

    if (node == NULL || node->next == NULL) {
        return;
    }

    _ced_list_split(node, &left, &right);

    _ced_list_merge_sort(&left, cmp);
    _ced_list_merge_sort(&right, cmp);

    *head = _ced_list_merge(left, right, cmp);
}

void ced_list_sort(ced_list_p list, ced_data_cmp cmp) {
    assert(list != NULL);
    ced_data_cmp _cmp = ced_data_cmp_default;

    if (cmp != NULL) {
        _cmp = cmp;
    }

    _ced_list_merge_sort(&list->head, _cmp);
}