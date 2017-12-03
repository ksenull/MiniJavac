//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_PRINTSTAT_H
#define AST_PRINTSTAT_H
#include "../IStatement.h"
#include "../../IVisitor.h"
#include "../IExpression.h"

namespace AST {
    class PrintStatement : IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }
    private:
        const IExpression* expression;
    };
}
#endif //AST_PRINTSTAT_H
