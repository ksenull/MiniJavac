#pragma once

#include "IVisitor.h"

namespace ast {

    class PrintVisitor : IVisitor<void> {
    public:

#define DECLARE_PRINT_VISIT(NODE)  void visit(const nodes::NODE* node) const override;

        DECLARE_PRINT_VISIT(Program)
        DECLARE_PRINT_VISIT(MainClass)
        DECLARE_PRINT_VISIT(Identifier)
        DECLARE_PRINT_VISIT(Assign)
        DECLARE_PRINT_VISIT(IfElse)
        DECLARE_PRINT_VISIT(While)
        DECLARE_PRINT_VISIT(Print)
        DECLARE_PRINT_VISIT(GetItem)

        DECLARE_PRINT_VISIT(And)
        DECLARE_PRINT_VISIT(Less)
        DECLARE_PRINT_VISIT(Plus)
        DECLARE_PRINT_VISIT(Minus)
        DECLARE_PRINT_VISIT(Mult)


#undef DECLARE_PRINT_VISIT
    };


 }