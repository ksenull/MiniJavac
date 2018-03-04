#pragma once

#include <vector>
#include "../IVisitor.h"

namespace ast {
    namespace nodes {

        class Node {
        public:
            virtual void accept(IVisitor<void>* visitor) const = 0;
        };


        class NodeList {
            std::vector<Node*> list;
        public:
            void add(Node* node) {
                list.emplace_back(node);
            }

            Node* at(unsigned long i) {
                return list.at(i);
            }

            unsigned long size() {
                return list.size();
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