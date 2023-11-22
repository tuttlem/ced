#ifndef __ced_cont_graph_h__
#define __ced_cont_graph_h__

#include <assert.h>
#include <stdlib.h>

#include "./types.h"
#include "./list.h"

typedef struct ced_graph_node_t {
    CED_REFLECT_INFO

    void *data;
} ced_graph_node_t, *ced_graph_node_p;

typedef struct ced_graph_edge_t {
    CED_REFLECT_INFO

    ced_graph_node_p from;
    ced_graph_node_p to;

    void *data;
} ced_graph_edge_t, *ced_graph_edge_p;

typedef struct ced_graph_t {
    CED_REFLECT_INFO

    ced_list_p nodes;
    ced_list_p edges;
} ced_graph_t, *ced_graph_p;

/**
 * @brief Creates a new graph
 * @return A pointer to the new graph
 */
ced_graph_p ced_graph_new();

/**
 * @brief Frees a graph
 * @param graph The graph to free
 */
void ced_graph_free(ced_graph_p graph);

/**
 * @brief Adds a new node to the graph
 * @param graph The graph to add the node to
 * @param data The data to store in the node
 * @return A pointer to the new node
 */
ced_graph_node_p ced_graph_add_node(ced_graph_p graph, void *data);

/**
 * @brief Adds a new edge to the graph
 * @param graph The graph to add the edge to
 * @param from The node to start the edge from
 * @param to The node to end the edge at
 * @param data The data to store in the edge
 */
ced_graph_edge_p ced_graph_add_edge(ced_graph_p graph, ced_graph_node_p from, ced_graph_node_p to, void *data);

/**
 * @brief Finds a node in the graph
 * @param graph The graph to search
 * @param data The data to search for
 * @param cmp The comparison function to use
 * @return A pointer to the node if found, NULL otherwise
 */
ced_graph_node_p ced_graph_find_node(ced_graph_p graph, ced_data_cmp cmp, void *data);

/**
 * @brief Removes a node from the graph
 * @param graph The graph to remove the node from
 * @param node The node to remove
 */
void ced_graph_remove_node(ced_graph_p graph, ced_graph_node_p node);

/**
 * @brief Finds an edge in the graph
 * @param graph The graph to search
 * @param data The data to search for
 * @param cmp The comparison function to use
 * @return A pointer to the edge if found, NULL otherwise
 */
ced_graph_edge_p ced_graph_find_edge(ced_graph_p graph, ced_data_cmp cmp, void *data);

/**
 * @brief Removes an edge from the graph
 * @param graph The graph to remove the edge from
 * @param edge The edge to remove
 */
void ced_graph_remove_edge(ced_graph_p graph, ced_graph_edge_p edge);

/**
 * @brief Finds a path between two nodes
 * @param graph The graph to search
 * @param from The starting node
 * @param to The ending node
 * @return A list of nodes representing the path
 */
ced_list_p ced_graph_find_path(ced_graph_p graph, ced_graph_node_p from, ced_graph_node_p to);

#endif /* __ced_cont_graph_h__ */

