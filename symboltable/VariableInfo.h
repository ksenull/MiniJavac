#pragma once

#include "Symbol.h"
#include "../ast/nodes/Nodes.h"


namespace symboltable {
    class VariableInfo : public IInfo {
    public:
        explicit VariableInfo(const common::Location& loc) : IInfo(loc) {}

        void BuildFromAst(ast::nodes::VariableDeclaration* var);
    private:
        ast::nodes::Type* type {};
    };
}