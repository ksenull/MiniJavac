//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_NEWEXP_H
#define AST_NEWEXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const Identifier *className;
    };
}
#endif //AST_NEWEXP_H
