//
// Created by kitnoel on 03.12.17.
//

#ifndef MINIJAVAC_IVISITOR_H
#define MINIJAVAC_IVISITOR_H

#include "Nodes/Identifier.h"

namespace AST {
    class IVisitor {
    public:
        void visit(const Identifier *identifier);


    };
}

#endif //MINIJAVAC_IVISITOR_H
