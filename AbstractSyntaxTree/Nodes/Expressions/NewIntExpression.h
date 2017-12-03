//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_NEWINTEXPRESSION_H
#define AST_NEWINTEXPRESSION_H
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MultExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression* size;
    };
}
#endif //AST_NEWINTEXPRESSION_H
