#pragma once

#include <vector>
#include "../IVisitor.h"

namespace ast {
    namespace nodes {

        class Node {
        public:
            virtual void accept(IVisitor<void>* visitor) const = 0;
        };


        class NodeList : public std::vector<Node*> {
        public:
            NodeList() = default;
            NodeList(Node* node, NodeList* _nodeList) : NodeList(*_nodeList) {
                emplace_back(node);
            }
        };


#define DECLARE_PRINT_ACCEPT(ACCEPTOR) \
        void accept(IVisitor<void>* visitor) const;

#define DEFINE_PRINT_ACCEPT(ACCEPTOR) \
        void ACCEPTOR::accept(IVisitor<void>* visitor) const { \
            visitor->visit(this); \
        }

    }
}