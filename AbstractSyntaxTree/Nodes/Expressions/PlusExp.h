//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_PLUSEXP_H
#define AST_PLUSEXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class PlusExp : IExpression {
    public:
        int accept(IVisitor& visitor) const {
            return visitor.visit(this);
        }
    private:
        const IExpression* left;
        const IExpression* right;
    };
}

#endif //AST_PLUSEXP_H
