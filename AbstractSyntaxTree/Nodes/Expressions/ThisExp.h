//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_THISEXP_H
#define AST_THISEXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }
    };
}
#endif //AST_THISEXP_H
