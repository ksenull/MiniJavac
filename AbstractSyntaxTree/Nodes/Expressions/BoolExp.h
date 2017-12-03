//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_BOOLEXP_H
#define AST_BOOLEXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        bool value;
    };
}
#endif //AST_BOOLEXP_H
