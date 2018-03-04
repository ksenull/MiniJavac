#pragma once

#include <vector>
#include "../IVisitor.h"

namespace ast {
    namespace nodes {
        class Node  {
        public:
            virtual void accept(IVisitor* visitor) const = 0;
        };

        class NodeList {
            std::vector<Node*> list;
        public:
            void add(const Node* node) {
                list.emplace_back(node);
            }

            Node* at(unsigned long i) {
                return list.at(i);
            }

            unsigned long size() {
                return list.size();
            }
        };

#define DECLARE_ACCEPT(ACCEPTOR) \
        void ACCEPTOR::accept(IVisitor* visitor) const;

#define DEFINE_ACCEPT(ACCEPTOR) \
        void ACCEPTOR::accept(IVisitor* visitor) const{ \
            visitor->visit(this); \
        }

    }
}