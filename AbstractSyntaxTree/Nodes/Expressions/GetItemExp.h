//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_GETITEMEXP_H
#define AST_GETITEMEXP_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class GetItemExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *arr;
        const IExpression *index;
    };
}
#endif //AST_GETITEMEXP_H
