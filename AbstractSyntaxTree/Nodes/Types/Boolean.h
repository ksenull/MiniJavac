//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_BOOLEAN_H
#define AST_BOOLEAN_H
#include "../Type.h"
#include "../../IVisitor.h"

namespace AST {
    class Boolean : public Type {
    public:
        void Accept(IVisitor* visitor) const {
            return visitor->visit(this);
        }
    };
}
#endif //AST_BOOLEAN_H
