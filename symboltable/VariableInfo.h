#pragma once

#include "Symbol.h"
#include "../ast/nodes/Nodes.h"


namespace symboltable {
    struct VariableInfo : IInfo {
        explicit VariableInfo(const common::Location& loc) : IInfo(loc) {}
        void BuildFromAst(ast::nodes::VariableDeclaration* var);
    };
}