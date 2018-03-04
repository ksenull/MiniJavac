#pragma once

#include "nodes/Program.h"

namespace ast {
    class IVisitor {
    public:
        virtual void visit(const nodes::Program* program) const = 0;
        virtual void visit(const nodes::MainClass* mainClass) const = 0;
    };
}
