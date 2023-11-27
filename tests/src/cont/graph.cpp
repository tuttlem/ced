//
// Created by michael on 10/11/23.
//

#include "gtest/gtest.h"
#include "ced.h"
#include <iostream>

namespace {
    void print_graph(ced_graph_p graph) {
        std::cout << "Nodes:" << std::endl;
        ced_list_node_p node;
        ced_list_foreach(node, graph->nodes) {
            std::cout << node->data << " (" << ((ced_graph_node_p)node->data)->data << ")" << std::endl;
        }

        std::cout << "Edges:" << std::endl;
        ced_list_node_p edge;
        ced_list_foreach(edge, graph->edges) {
            std::cout << ((ced_graph_edge_p)edge->data)->from->data << " -> " << ((ced_graph_edge_p)edge->data)->to->data << std::endl;
        }
    }

    TEST(GraphTests, Construction) {
        ced_graph_p graph = ced_graph_new();
        EXPECT_EQ(graph->nodes->size, 0);
        EXPECT_EQ(graph->edges->size, 0);
        ced_graph_free(graph);
    }
    TEST(GraphTests, AddNode) {
        ced_graph_p graph = ced_graph_new();
        ced_graph_node_p node = ced_graph_add_node(graph, (void *)1);
        EXPECT_EQ(graph->nodes->size, 1);
        EXPECT_EQ(node->data, (void *)1);
        ced_graph_free(graph);
    }
    TEST(GraphTests, AddEdge) {
        ced_graph_p graph = ced_graph_new();
        ced_graph_node_p node1 = ced_graph_add_node(graph, (void *)1);
        ced_graph_node_p node2 = ced_graph_add_node(graph, (void *)2);
        ced_graph_edge_p edge = ced_graph_add_edge(graph, node1, node2, (void *)3);
        EXPECT_EQ(graph->edges->size, 1);
        EXPECT_EQ(edge->from, node1);
        EXPECT_EQ(edge->to, node2);
        EXPECT_EQ(edge->data, (void *)3);
        ced_graph_free(graph);
    }
    TEST(GraphTests, FindPathInGraph) {
        ced_graph_p graph = ced_graph_new();
        ced_graph_node_p node1 = ced_graph_add_node(graph, (void *)1);
        ced_graph_node_p node2 = ced_graph_add_node(graph, (void *)2);
        ced_graph_node_p node3 = ced_graph_add_node(graph, (void *)3);
        ced_graph_node_p node4 = ced_graph_add_node(graph, (void *)4);
        ced_graph_edge_p edge12 = ced_graph_add_edge(graph, node1, node2, (void *)9);
        ced_graph_edge_p edge23 = ced_graph_add_edge(graph, node2, node3, (void *)18);
        ced_graph_edge_p edge34 = ced_graph_add_edge(graph, node3, node4, (void *)27);

        ced_list_p path = ced_graph_find_path(graph, node1, node4);

        EXPECT_EQ(path->size, 3);
        EXPECT_EQ(((ced_graph_edge_p)path->head->data)->data, (void *)9);
        EXPECT_EQ(((ced_graph_edge_p)path->head->next->data)->data, (void *)18);
        EXPECT_EQ(((ced_graph_edge_p)path->head->next->next->data)->data, (void *)27);

        ced_list_free(path);
        ced_graph_free(graph);
    }

    TEST(GraphTests, PathNotFoundInGraph) {
        ced_graph_p graph = ced_graph_new();
        ced_graph_node_p node1 = ced_graph_add_node(graph, (void *)1);
        ced_graph_node_p node2 = ced_graph_add_node(graph, (void *)2);
        ced_graph_node_p node3 = ced_graph_add_node(graph, (void *)3);
        ced_graph_node_p node4 = ced_graph_add_node(graph, (void *)4);
        ced_graph_edge_p edge12 = ced_graph_add_edge(graph, node1, node2, (void *)9);
        ced_graph_edge_p edge23 = ced_graph_add_edge(graph, node2, node3, (void *)18);

        ced_list_p path = ced_graph_find_path(graph, node1, node4);

        EXPECT_EQ(path, (ced_list_p)NULL);

        ced_graph_free(graph);
    }


}