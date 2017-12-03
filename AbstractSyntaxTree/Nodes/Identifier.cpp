//
// Created by kitnoel on 03.12.17.
//

#include "../IVisitor.h"
#include "Identifier.h"

void Identifier::Accept(IVisitor &visitor) const {
    return visitor.visit(this);
}
