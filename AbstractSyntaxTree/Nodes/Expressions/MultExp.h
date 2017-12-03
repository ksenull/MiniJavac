//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_MULTEXP_H
#define AST_MULTEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *left;
        const IExpression *right;
    };
}

#endif //AST_MULTEXP_H
