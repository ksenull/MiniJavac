//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_NOTEXP_H
#define AST_NOTEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }
    private:
        const IExpression* exp;
    };
}
#endif //AST_NOTEXP_H
