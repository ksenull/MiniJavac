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
            Graph();
//            explicit Graph(const GraphType& gt = GT_Directed);
            ~Graph();

            void initialise(const GraphType& gt);

            void release();

            Node addNode(const std::string& name);

            void addEdge(const Node& from, const Node& to);

            void readFromFile(const std::string& filename);

            void savePng(const std::string& filename);
        private:
            Agraph_t* graph;
            GVC_t* gvc;
        };
    }
}