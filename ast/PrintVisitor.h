#pragma once

#include "IVisitor.h"

namespace ast {

#define DECLARE_VISIT(NODE) \
    void visit(const nodes::NODE* node) const override;

    class PrintVisitor : IVisitor {
        DECLARE_VISIT(Program)
        DECLARE_VISIT(MainClass)
        DECLARE_VISIT(Identifier)
        DECLARE_VISIT(Assign)
        DECLARE_VISIT(IfElse)
        DECLARE_VISIT(While)
        DECLARE_VISIT(Print)
        DECLARE_VISIT(GetItem)
    };

#undef DECLARE_VISIT

 }