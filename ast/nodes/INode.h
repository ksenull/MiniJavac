#pragma once

#include <vector>
#include "../PrintVisitor.h"
#include "../../common/Located.h"

namespace ast {
    namespace nodes {

        using Location = common::Location;

        struct INode : common::Located {
            INode() = default;
            INode(const Location& loc) : Located(std::move(loc)) {}
            virtual ~INode() = default;
            virtual void accept(const IVisitor<void>* visitor) const = 0;
//            Location loc;
        };

        struct IStatement : public INode {
            IStatement() = default;
            IStatement(const Location& loc) : INode(loc) {};
        };

        struct IExpression : public INode {
            IExpression() = default;
            IExpression(const Location& loc) : INode(loc) {};
        };

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