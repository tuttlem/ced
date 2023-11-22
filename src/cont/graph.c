
#include "./graph.h"

/**
 * @brief Creates a new graph
 * @return A pointer to the new graph
 */
ced_graph_p ced_graph_new() {
    ced_graph_p graph = malloc(sizeof(ced_graph_t));
    assert(graph != NULL);

    ced_reflect_set_info(graph, reflect_type_graph);

    graph->nodes = ced_list_new();
    graph->nodes->managed_data = 1;

    graph->edges = ced_list_new();
    graph->edges->managed_data = 1;

    return graph;
}

/**
 * @brief Frees a graph
 * @param graph The graph to free
 */
void ced_graph_free(ced_graph_p graph) {
    assert(graph != NULL);

    ced_list_free(graph->edges);
    ced_list_free(graph->nodes);

    free(graph);
}

/**
 * @brief Adds a new node to the graph
 * @param graph The graph to add the node to
 * @param data The data to store in the node
 * @return A pointer to the new node
 */
ced_graph_node_p ced_graph_add_node(ced_graph_p graph, void *data) {
    assert(graph != NULL);

    ced_graph_node_p node = malloc(sizeof(ced_graph_node_t));
    assert(node != NULL);

    ced_reflect_set_info(node, reflect_type_graph_node);
    node->data = data;

    ced_list_append(graph->nodes, node);

    return node;
}

/**
 * @brief Adds a new edge to the graph
 * @param graph The graph to add the edge to
 * @param from The node to start the edge from
 * @param to The node to end the edge at
 * @param data The data to store in the edge
 */
ced_graph_edge_p ced_graph_add_edge(ced_graph_p graph, ced_graph_node_p from, ced_graph_node_p to, void *data) {
    assert(graph != NULL);

    ced_graph_edge_p edge = malloc(sizeof(ced_graph_edge_t));
    assert(edge != NULL);

    ced_reflect_set_info(edge, reflect_type_graph_edge);
    edge->from = from;
    edge->to = to;
    edge->data = data;

    ced_list_append(graph->edges, edge);

    return edge;
}

/**
 * @brief Finds a node in the graph
 * @param graph The graph to search
 * @param data The data to search for
 * @param cmp The comparison function to use
 * @return A pointer to the node if found, NULL otherwise
 */
ced_graph_node_p ced_graph_find_node(ced_graph_p graph, ced_data_cmp cmp, void *data) {
    assert(graph != NULL);
    return ced_list_find(graph->nodes, cmp, data);
}

/**
 * @brief Removes a node from the graph
 * @param graph The graph to remove the node from
 * @param node The node to remove
 */
void ced_graph_remove_node(ced_graph_p graph, ced_graph_node_p node) {
    assert(graph != NULL);
    assert(node != NULL);

    ced_list_remove(graph->nodes, NULL, node);
}

/**
 * @brief Finds an edge in the graph
 * @param graph The graph to search
 * @param data The data to search for
 * @param cmp The comparison function to use
 * @return A pointer to the edge if found, NULL otherwise
 */
ced_graph_edge_p ced_graph_find_edge(ced_graph_p graph, ced_data_cmp cmp, void *data) {
    assert(graph != NULL);
    return ced_list_find(graph->edges, cmp, data);
}

/**
 * @brief Removes an edge from the graph
 * @param graph The graph to remove the edge from
 * @param edge The edge to remove
 */
void ced_graph_remove_edge(ced_graph_p graph, ced_graph_edge_p edge) {
    assert(graph != NULL);
    assert(edge != NULL);

    ced_list_remove(graph->edges, NULL, edge);
}

int ced_graph_edge_cmp_from(const void *_edge, const void *_node) {
    assert(_edge != NULL);
    assert(_node != NULL);

    ced_graph_edge_p edge = (ced_graph_edge_p)_edge;
    ced_graph_node_p node = (ced_graph_node_p)_node;

    return edge->from < node ? -1 : edge->from > node ? 1 : 0;
}

int ced_graph_edge_cmp_to(const void *_edge, const void *_node) {
    assert(_edge != NULL);
    assert(_node != NULL);

    ced_graph_edge_p edge = (ced_graph_edge_p)_edge;
    ced_graph_node_p node = (ced_graph_node_p)_node;

    return edge->to == node;
}

int ced_graph_edge_cmp_either(const void *_edge, const void *_node) {
    assert(_edge != NULL);
    assert(_node != NULL);

    ced_graph_edge_p edge = (ced_graph_edge_p)_edge;
    ced_graph_node_p node = (ced_graph_node_p)_node;

    return edge->to == node || edge->from == node;
}

int _ced_graph_is_node_in_path(ced_list_p path, ced_graph_node_p node) {
    return ced_list_find(path, NULL, node) != NULL;
}

void _ced_graph_find_path_recur(ced_graph_p graph, ced_graph_node_p from, ced_graph_node_p to, ced_list_p path) {
    assert(graph != NULL);
    assert(from != NULL);
    assert(to != NULL);
    assert(path != NULL);

    // find an edge that starts at the starting node
    ced_graph_edge_p edge = NULL;
    ced_list_node_p edge_iter;

    ced_list_foreach(edge_iter, graph->edges) {
        ced_graph_edge_p edge_iter_data = edge_iter->data;
        if (edge_iter_data->from == from) {
            edge = edge_iter_data;
            break;
        }
    }

    // if there is no edge, return
    if (edge == NULL || edge->to == NULL) {
        return;
    }

    // if the edge ends at the ending node, add it to the path and return
    if (edge->to == to) {
        ced_list_append(path, edge);
        return;
    }

    // if the edge ends at a node that is already in the path, return
    if (_ced_graph_is_node_in_path(path, edge->to->data)) {
        return;
    }

    // add the edge to the path
    ced_list_append(path, edge);

    // find a path from the edge's end node to the ending node
    _ced_graph_find_path_recur(graph, edge->to, to, path);
}


/**
 * @brief Finds a path between two nodes
 * @param graph The graph to search
 * @param from The starting node
 * @param to The ending node
 * @return A list of nodes representing the path
 */
ced_list_p ced_graph_find_path(ced_graph_p graph, ced_graph_node_p from, ced_graph_node_p to) {
    assert(graph != NULL);
    assert(from != NULL);
    assert(to != NULL);

    ced_list_p path = ced_list_new();

    // start the search
    _ced_graph_find_path_recur(graph, from, to, path);

    // initial validation that we found a path
    if (path->size == 0) {
        ced_list_free(path);
        return NULL;
    }

    // final validation step that we have the correct path
    ced_graph_node_p from_in_path = ((ced_graph_edge_p)path->head->data)->from;
    ced_graph_node_p to_in_path = ((ced_graph_edge_p)path->tail->data)->to;

    if (from_in_path != from || to_in_path != to) {
        ced_list_free(path);
        return NULL;
    }

    return path;
}
