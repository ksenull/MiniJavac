#pragma once

#include "Expressions.h"

namespace ir {
namespace tree {

    struct IStatement : INode {
    };

    struct StatementList : INodeList {
    };

    struct MoveStatement : IStatement {
        MoveStatement(IExpression* target, IExpression* source) : target(target),
                                                                  source(source) {}

        IExpression* target;
        IExpression* source;
    };

    struct ExpStatement : IStatement { // evaluates e and discards the result
        explicit ExpStatement(IExpression* exp) : exp(exp) {}

        IExpression* exp;
    };

    struct JumpStatement : IStatement {
        explicit JumpStatement(const Label& target) : target(target) {}

        Label target;
    };

    struct CondJumpStatement : IStatement {
        CondJumpStatement(IExpression* left, RelationalOperation op, IExpression* right,
        const Label& ifTarget, const Label& elseTarget) : left(left), op(op), right(right),
                                                          ifTarget(ifTarget), elseTarget(elseTarget) {}

        IExpression* left;
        RelationalOperation op;
        IExpression* right;
        Label ifTarget;
        Label elseTarget;
    };

    struct SeqStatement : IStatement {
        SeqStatement(StatementList* stms) : stms(stms) {}

        StatementList* stms;
    };

    struct LabelStatement : IStatement { // like label in asm
        LabelStatement(const Label& label) : label(label) {}

        Label label;
    };
}
}