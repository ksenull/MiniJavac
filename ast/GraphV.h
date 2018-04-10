#pragma once

#include <iostream>
#include <gvc.h>

namespace ast {
    namespace visualize {
        enum GraphType {
            GT_Directed,
            GT_Undirected,
        };

        struct Node {
            Agnode_t* node;
        };

        class Graph {
        public:
            explicit Graph(const GraphType& gt = GT_Directed);
            ~Graph();
            void release();

            Node addNode(const std::string& name);

            void addEdge(const Node& from, const Node& to);

            void savePng(const std::string& filename);
        private:
            Agraph_t* graph;
            GVC_t* gvc;
        };
    }
}