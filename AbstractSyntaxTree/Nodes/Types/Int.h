//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_INT_H
#define AST_INT_H
#include "../Type.h"
#include "../../IVisitor.h"

namespace AST {
    class Int : public Type {
    public:
        void Accept(IVisitor* visitor) const {
            return visitor->visit(this);
        }
    };
}
#endif //AST_INT_H
