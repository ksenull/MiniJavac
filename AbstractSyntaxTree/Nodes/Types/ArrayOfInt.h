//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_ARRAYOFINT_H
#define AST_ARRAYOFINT_H

#include "../Type.h"
#include "../../IVisitor.h"

namespace AST {
    class ArrayOfInt : public Type {
    public:
        void Accept(IVisitor* visitor) const {
            return visitor->visit(this);
        }
    };
}
#endif //AST_ARRAYOFINT_H
