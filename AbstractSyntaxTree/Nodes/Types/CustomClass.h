//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_CUSTOMCLASS_H
#define AST_CUSTOMCLASS_H
#include "../Type.h"
#include "../../IVisitor.h"

namespace AST {
    class CustomClass : public Type {
    public:
        void Accept(IVisitor* visitor) const {
            return visitor->visit(this);
        }

    private:
        const Identifier* className;
    };
}
#endif //AST_CUSTOMCLASS_H
