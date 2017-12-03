//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_ASSIGNSTAT_H
#define AST_ASSIGNSTAT_H
#include "../../IVisitor.h"
#include "../IExpression.h"
#include "../IStatement.h"

namespace AST {
    class AssignStatement : IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }
    private:
        const Identifier* lvalue;
        const IExpression* rvalue;
    };

    class AssignItemStatement: IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }

    private:
        const Identifier* arrName;
        const IExpression* index;
        const IExpression* rvalue;
    };
}
#endif //AST_ASSIGNSTAT_H
