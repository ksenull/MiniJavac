#pragma once

#include <vector>
#include "../PrintVisitor.h"

namespace ast {
    namespace nodes {

        struct INode {
            virtual void accept(IVisitor<void>* visitor) const = 0;
        };

        struct IStatement : public INode {};

        struct IExpression : public INode {};

        struct INodeList : public INode {
            INodeList() = default;

            std::vector<INode*> nodes;
        };


#define DEFINE_PRINT_ACCEPT \
        void accept(const IVisitor<void>* visitor) const { \
            visitor->visit(this); \
        }

    }
}