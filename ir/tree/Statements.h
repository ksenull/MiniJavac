#pragma once

#include "Expressions.h"

namespace ir {
namespace tree {
    
#define DEFINE_PRINT_ACCEPT \
        void accept(const IVisitor<void>* visitor) const override { \
            visitor->visit(this); \
        }

    struct IStatement : INode {
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct CStatementList : INodeList {
    };

    struct CMoveStatement : IStatement {
        CMoveStatement(IExpression* target, IExpression* source) : target(target),
                                                                  source(source) {}
        DEFINE_PRINT_ACCEPT

        IExpression* target;
        IExpression* source;
    };

    struct CExpStatement : IStatement { // evaluates e and discards the result
        explicit CExpStatement(IExpression* exp) : exp(exp) {}
        DEFINE_PRINT_ACCEPT

        IExpression* exp;
    };

    struct CJumpStatement : IStatement {
        explicit CJumpStatement(const Label& target) : target(target) {}
        DEFINE_PRINT_ACCEPT

        Label target;
    };

    struct CCondJumpStatement : IStatement {
        CCondJumpStatement(IExpression* left, RelationalOperation op, IExpression* right,
        const Label& ifTarget, const Label& elseTarget) : left(left), op(op), right(right),
                                                          ifTarget(ifTarget), elseTarget(elseTarget) {}
        DEFINE_PRINT_ACCEPT

        IExpression* left;
        RelationalOperation op;
        IExpression* right;
        Label ifTarget;
        Label elseTarget;
    };

    struct CSeqStatement : IStatement {
        CSeqStatement(IStatement* left, IStatement* right) : left(left), right(right) {}
        DEFINE_PRINT_ACCEPT

        IStatement* left;
        IStatement* right;
    };

    struct CLabelStatement : IStatement { // like label in asm
        CLabelStatement(const Label& label) : label(label) {}
        DEFINE_PRINT_ACCEPT

        Label label;
    };

#undef DEFINE_PRINT_ACCEPT
}
}