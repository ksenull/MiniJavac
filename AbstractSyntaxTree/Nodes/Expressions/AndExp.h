//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_ANDEXP_H
#define AST_ANDEXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class AndExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *left;
        const IExpression *right;
    };
}

#endif //AST_ANDEXP_H
