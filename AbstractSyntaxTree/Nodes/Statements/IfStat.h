//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_IFSTAT_H
#define AST_IFSTAT_H
#include "../IStatement.h"
#include "../../IVisitor.h"
#include "../IExpression.h"

namespace AST {
    class IfStatement : IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }
    private:
        const IExpression* condition;
        const IStatement* ifBody;
        const IStatement* elseBody;
    };
}
#endif //AST_IFSTAT_H
