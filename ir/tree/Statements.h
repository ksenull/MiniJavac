#pragma once

#include "Expressions.h"

namespace ir {
namespace tree {

    struct IStatement : INode {
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct StatementList : INodeList {
    };

    struct MoveStatement : IStatement {
        MoveStatement(IExpression* target, IExpression* source) : target(target),
                                                                  source(source) {}
        DEFINE_PRINT_ACCEPT

        IExpression* target;
        IExpression* source;
    };

    struct ExpStatement : IStatement { // evaluates e and discards the result
        explicit ExpStatement(IExpression* exp) : exp(exp) {}
        DEFINE_PRINT_ACCEPT

        IExpression* exp;
    };

    struct JumpStatement : IStatement {
        explicit JumpStatement(const Label& target) : target(target) {}
        DEFINE_PRINT_ACCEPT

        Label target;
    };

    struct CondJumpStatement : IStatement {
        CondJumpStatement(IExpression* left, RelationalOperation op, IExpression* right,
        const Label& ifTarget, const Label& elseTarget) : left(left), op(op), right(right),
                                                          ifTarget(ifTarget), elseTarget(elseTarget) {}
        DEFINE_PRINT_ACCEPT

        IExpression* left;
        RelationalOperation op;
        IExpression* right;
        Label ifTarget;
        Label elseTarget;
    };

    struct SeqStatement : IStatement {
        SeqStatement(IStatement* left, IStatement* right) : left(left), right(right) {}
        DEFINE_PRINT_ACCEPT

        IStatement* left;
        IStatement* right;
    };

    struct LabelStatement : IStatement { // like label in asm
        LabelStatement(const Label& label) : label(label) {}
        DEFINE_PRINT_ACCEPT

        Label label;
    };
}
}