//
// Created by ksenull on 4/9/18.
//
#include "GraphV.h"

namespace ast {
    namespace visualize {
        Graph::Graph() {
            gvc = gvContext();
        }
//        Graph::Graph(const GraphType& gt) {
//            gvc = gvContext();
//            switch (gt) {
//                case GT_Directed:
//                    graph = agopen("Test", Agdirected, 0);
//                    break;
//                case GT_Undirected:
//                    graph = agopen("Test", Agundirected, 0);
//                    break;
//                default:
//                    ;
//            }
//        }
        Graph::~Graph() {
            gvFreeContext(gvc);
        }

        void Graph::initialise(const GraphType& gt) {
            gvc = gvContext();
            switch (gt) {
            case GT_Directed:
                graph = agopen("Test", Agdirected, 0);
                break;
            case GT_Undirected:
                graph = agopen("Test", Agundirected, 0);
                break;
            default:
                ;
        }

        }
        Node Graph::addNode(const std::string& name) {
            auto* node = agnode(graph, const_cast<char*>(name.c_str()), 1);
            Node n{node};
            return n;
        }

        void Graph::addEdge(const Node& from, const Node& to) {
            auto edge = agedge(graph, from.node, to.node, const_cast<char *>("-"), 1);
        }

        void Graph::savePng(const std::string& filename) {
            gvLayout(gvc, graph, "dot");
            gvRenderFilename (gvc, graph, "png", filename.c_str());
        }

        void Graph::release() {
            gvFreeLayout(gvc, graph);
            agclose(graph);
        }

        void Graph::readFromFile(const std::string& filename) {
            {
                auto* fp = fopen(filename.c_str(), "r");
                graph = agread(fp, 0);
            }
        }
    }
}