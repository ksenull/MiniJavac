//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_LESSEXP_H
#define AST_LESSEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class LessExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *left;
        const IExpression *right;
    };
}
#endif //AST_LESSEXP_H
