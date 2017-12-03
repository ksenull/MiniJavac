//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_MINUSEXP_H
#define AST_MINUSEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MinusExp : IExpression {
    public:
        int accept(IVisitor& visitor) const {
            return visitor.visit(this);
        }
    private:
        const IExpression* left;
        const IExpression* right;
    };

#endif //AST_MINUSEXP_H
