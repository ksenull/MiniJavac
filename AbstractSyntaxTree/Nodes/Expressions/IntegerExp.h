//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_INTEGEREXP_H
#define AST_INTEGEREXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class IntegerExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        int value;
    };
}

#endif //AST_INTEGEREXP_H
