#pragma once

#include "Expressions.h"

namespace ir {
namespace tree {

    struct IStatement : INode {

    };

    struct StatementList : INodeList {
    };

    struct MoveStatement : IStatement {
        IExpression* target;
        IExpression* source;
    };

    struct ExpStatement : IStatement { // evaluates e and discards the result
        IExpression* exp;
    };

    struct JumpStatement : IStatement {
        Label target;
    };

    struct CondJumpStatement : IStatement {
        IExpression* left;
        RelationalOperation op;
        IExpression* right;
        Label ifTarget;
        Label elseTarget;
    };

    struct SeqStatement : IStatement {
        StatementList* stms;
    };

    struct LabelStatement : IStatement { // like label in asm
        Label label;
    };
}
}