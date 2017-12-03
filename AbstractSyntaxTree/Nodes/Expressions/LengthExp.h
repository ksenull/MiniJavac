//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_LENGTHEXP_H
#define AST_LENGTHEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class LengthExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *item;
    };
}
#endif //AST_LENGTHEXP_H
