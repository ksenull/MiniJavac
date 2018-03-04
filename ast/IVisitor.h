#pragma once

#include <Statement.h>
#include <Identifier.h>
#include <MainClass.h>
#include "Program.h"

namespace ast {

#define DECLARE_IVISIT(NODE) \
    virtual void visit(const nodes::NODE* node) const = 0;

    class IVisitor {
    public:
        DECLARE_IVISIT(Program)
        DECLARE_IVISIT(MainClass)
        DECLARE_IVISIT(Identifier)
        DECLARE_IVISIT(Assign)
        DECLARE_IVISIT(IfElse)
        DECLARE_IVISIT(While)
        DECLARE_IVISIT(Print)
        DECLARE_IVISIT(GetItem)
    };

#undef DECLARE_IVISIT
}
