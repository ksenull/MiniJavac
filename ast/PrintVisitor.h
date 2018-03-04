#pragma once

#include "IVisitor.h"

namespace ast {

    class PrintVisitor : IVisitor {
        void visit(const nodes::Program* program) const;
        void visit(const nodes::MainClass* mainClass) const;
    };

 }