#pragma once

#include "IVisitor.h"

namespace ast {

    class PrintVisitor : IVisitor {
        void visit(const nodes::Program* program) const override;
        void visit(const nodes::MainClass* mainClass) const override;
        void visit(const nodes::Identifier* id) const;
    };

 }