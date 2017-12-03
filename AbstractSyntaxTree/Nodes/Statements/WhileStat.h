//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_WHILESTAT_H
#define AST_WHILESTAT_H
#include "../IStatement.h"
#include "../../IVisitor.h"
#include "../IExpression.h"

namespace AST {
    class WhileStatement : IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }
    private:
        const IExpression* condition;
        const* IStatement* body;
    };
}
#endif //AST_WHILESTAT_H
