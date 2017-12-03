//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_METHODCALL_H
#define AST_METHODCALL_H

#include <vector>
#include "../IExpression.h"
#include "../../IVisitor.h"

namespace AST {
    class MethodCallExp : IExpression {
    public:
        int accept(IVisitor &visitor) const {
            return visitor.visit(this);
        }

    private:
        const IExpression *item;
        const Identifier* name;
        std::vector<IExpression*> args;
    };
}

#endif //AST_METHODCALL_H
