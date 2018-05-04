#pragma once

#include <vector>
#include "../PrintVisitor.h"
#include "../../ir/translate/TranslateVisitor.h"
#include "../../common/Located.h"

namespace ast {
    namespace nodes {

        using Location = common::Location;

        struct INode : common::Located {
            INode() = default;
            INode(const Location& loc) : Located(std::move(loc)) {}
            virtual ~INode() = default;
            virtual void accept(const IVisitor<void>* visitor) const = 0;
            virtual ir::translate::ISubtreeWrapper* accept(const IVisitor<ir::translate::ISubtreeWrapper*>* visitor) const = 0;
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
            using Iterator = std::vector<INode*>::iterator;

//            INodeList() = default;
            INodeList(const Location& _loc) : INode(_loc) {}

            std::vector<INode*> nodes;
        };


    }
}