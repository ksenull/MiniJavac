#pragma once

#include <vector>
#include "../PrintVisitor.h"

namespace ast {
    namespace nodes {

        struct Location {
            struct Pos {
                unsigned line;
                unsigned col;

                Pos() = default;
                Pos(unsigned line, unsigned col) : line(line), col(col) {}
            };

            Pos begin;
            Pos end;

            Location() = default;
            ~Location() = default;
            Location(unsigned bl, unsigned bc, unsigned el, unsigned ec) : begin{bl, bc}, end{el, ec} {}
        };

        struct INode {
            INode() = default;
            INode(const Location& loc) : loc(std::move(loc)) {}
            virtual ~INode() = default;
            virtual void accept(const IVisitor<void>* visitor) const = 0;
            Location loc{};
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