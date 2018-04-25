#pragma once

#include "Symbol.h"
#include "../ast/nodes/Nodes.h"


namespace symboltable {
    struct VariableInfo : IInfo {
        VariableInfo(ast::nodes::VariableDeclaration* var);
    };
}