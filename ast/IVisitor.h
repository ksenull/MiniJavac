#pragma once

#include "Identifier.h"
#include "MainClass.h"
#include "Program.h"

namespace ast {
    class IVisitor {
    public:
        virtual void visit(const nodes::Program* program) const = 0;
        virtual void visit(const nodes::MainClass* mainClass) const = 0;
        virtual void visit(const nodes::Identifier* id) const = 0;
    };
}
