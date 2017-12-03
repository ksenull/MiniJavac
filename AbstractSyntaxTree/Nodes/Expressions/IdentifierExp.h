//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_IDENTIFIEREXP_H
#define AST_IDENTIFIEREXP_H

#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const Identifier* identifier;
    };
}
#endif //AST_IDENTIFIEREXP_H
