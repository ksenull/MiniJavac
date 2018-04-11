#pragma once

#include <vector>
#include "../PrintVisitor.h"

namespace ast {
    namespace nodes {

        class Node {
        public:
//            virtual void accept(PrintVisitor* visitor) const = 0;
        };


        class NodeList {
        public:
            NodeList() = default;

            NodeList(Node* node, NodeList* _nodeList) {
                if (_nodeList) {
                    nodes = _nodeList->nodes;
                }
                nodes.emplace_back(node);
            }
            std::vector<Node*> nodes;
        };


#define DECLARE_PRINT_ACCEPT(ACCEPTOR) \
        void accept(const PrintVisitor* visitor) const;

#define DEFINE_PRINT_ACCEPT(ACCEPTOR) \
        void ACCEPTOR::accept(const PrintVisitor* visitor) const { \
            visitor->visit(this); \
        }

    }
}