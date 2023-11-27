
#include "btree.h"

/**
 * @brief Creates a new binary tree
 * @return A pointer to the new binary tree
 */
ced_btree_p ced_btree_new(ced_data_cmp cmp) {
    ced_btree_p tree = malloc(sizeof(ced_btree_t));
    assert(tree != NULL);

    ced_reflect_set_info(tree, reflect_type_btree);

    tree->root = NULL;

    if (cmp == NULL) {
        tree->cmp = ced_data_cmp_default;
    } else {
        tree->cmp = cmp;
    }

    tree->size = 0;
    tree->managed_data = 0;

    return tree;
}

/**
 * @brief Frees a binary tree
 * @param tree The binary tree to free
 */
void ced_btree_free(ced_btree_p tree) {
    assert(tree != NULL);

    ced_btree_node_p node = tree->root;

    if (node != NULL) {
        ced_btree_node_free(node, tree->managed_data);
    }

    free(tree);
}

/**
 * @brief Creates a new binary tree node
 * @return A pointer to the new binary tree node
 */
ced_btree_node_p ced_btree_node_new() {
    ced_btree_node_p node = malloc(sizeof(ced_btree_node_t));
    assert(node != NULL);

    ced_reflect_set_info(node, reflect_type_btree_node);

    node->left = NULL;
    node->right = NULL;
    node->key = NULL;
    node->data = NULL;

    return node;
}

/**
 * @brief Frees a binary tree node
 * @param node The binary tree node to free
 * @param managed_data Whether or not the data should be freed
 */
void ced_btree_node_free(ced_btree_node_p node, int managed_data) {
    assert(node != NULL);

    if (node->left != NULL) {
        ced_btree_node_free(node->left, managed_data);
        node->left = NULL;
    }

    if (node->right != NULL) {
        ced_btree_node_free(node->right, managed_data);
        node->right = NULL;
    }

    if (managed_data) {
        free(node->data);
    }

    free(node);
}

/**
 * @brief Inserts data into a binary tree
 * @param tree The binary tree to insert into
 * @param key The key to insert
 * @param data The data to insert
 */
void ced_btree_insert(ced_btree_p tree, void *key, void *data) {
    assert(tree != NULL);

    ced_btree_node_p node = ced_btree_node_new();
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    if (tree->root == NULL) {
        tree->root = node;
    } else {
        ced_btree_node_p current = tree->root;
        ced_btree_node_p parent;

        while (1) {
            parent = current;

            if (tree->cmp(key, current->key) < 0) {
                current = current->left;

                if (current == NULL) {
                    parent->left = node;
                    break;
                }
            } else {
                current = current->right;

                if (current == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }
    }

    tree->size++;
}

/**
 * @brief Removes data from a binary tree
 * @param tree The binary tree to remove from
 * @param key The key to remove
 */
void ced_btree_remove(ced_btree_p tree, void *key) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;
    ced_btree_node_p parent = tree->root;

    int is_left_child = 1;

    while (tree->cmp(key, current->key) != 0) {
        parent = current;

        if (tree->cmp(key, current->key) < 0) {
            is_left_child = 1;
            current = current->left;
        } else {
            is_left_child = 0;
            current = current->right;
        }

        if (current == NULL) {
            return;
        }
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == tree->root) {
            tree->root = NULL;
        } else if (is_left_child) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->right == NULL) {
        if (current == tree->root) {
            tree->root = current->left;
        } else if (is_left_child) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else if (current->left == NULL) {
        if (current == tree->root) {
            tree->root = current->right;
        } else if (is_left_child) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else {
        ced_btree_node_p successor = ced_btree_find_successor(tree, current->key);

        if (current == tree->root) {
            tree->root = successor;
        } else if (is_left_child) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = current->left;
    }

    if (tree->managed_data) {
        free(current->data);
    }

    free(current);
    tree->size--;
}

/**
 * @brief Finds data in a binary tree
 * @param tree The binary tree to find in
 * @param key The key to find
 * @return A pointer to the data if found, NULL otherwise
 */
void *ced_btree_get(ced_btree_p tree, void *key) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;

    while (tree->cmp(key, current->key) != 0) {
        if (tree->cmp(key, current->key) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current == NULL) {
            return NULL;
        }
    }

    return current->data;
}

/**
 * @brief Finds the node with the requested key
 * @param tree The binary tree to find in
 * @param key The key to find
 * @return A pointer to the data if found, NULL otherwise
 */
ced_btree_node_p ced_btree_get_node(ced_btree_p tree, void *key) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;

    while (tree->cmp(key, current->key) != 0) {
        if (tree->cmp(key, current->key) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current == NULL) {
            return NULL;
        }
    }

    return current;
}

/**
 * @brief Finds the minimum data in a binary tree
 * @param tree The binary tree to find in
 * @return A pointer to the minimum data if found, NULL otherwise
 */
void *ced_btree_find_min(ced_btree_p tree) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;

    while (current->left != NULL) {
        current = current->left;
    }

    return current->data;
}

/**
 * @brief Finds the maximum data in a binary tree
 * @param tree The binary tree to find in
 * @return A pointer to the maximum data if found, NULL otherwise
 */
void *ced_btree_find_max(ced_btree_p tree) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;

    while (current->right != NULL) {
        current = current->right;
    }

    return current->data;
}

/**
 * @brief Finds the successor of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the successor of
 * @return A pointer to the successor data if found, NULL otherwise
 */
void *ced_btree_find_successor(ced_btree_p tree, void *key) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;
    ced_btree_node_p successor = NULL;

    while (current != NULL) {
        if (tree->cmp(key, current->key) < 0) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return successor->data;
}

/**
 * @brief Finds the predecessor of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the predecessor of
 * @return A pointer to the predecessor data if found, NULL otherwise
 */
void *ced_btree_find_predecessor(ced_btree_p tree, void *key) {
    assert(tree != NULL);

    ced_btree_node_p current = tree->root;
    ced_btree_node_p predecessor = NULL;

    while (current != NULL) {
        if (tree->cmp(key, current->key) > 0) {
            predecessor = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return predecessor->data;
}

/**
 * @brief Finds the depth of data in a binary tree
 * @param tree The binary tree to find in
 * @param data The data to find the depth of
 * @return The depth of the data in the binary tree
 */
size_t ced_btree_depth(ced_btree_p tree, void *key) {
    assert(tree != NULL);
    int depth = 0;

    ced_btree_node_p current = tree->root;

    while (tree->cmp(key, current->key) != 0) {
        if (tree->cmp(key, current->key) < 0) {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current == NULL) {
            return -1;
        }

        depth ++;
    }

    return depth;
}