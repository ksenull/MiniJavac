#pragma once

#include <unordered_map>
#include "Symbol.h"
#include "ClassInfo.h"
#include "../ast/nodes/Nodes.h"

namespace symboltable {
    class ModuleTable {
    public:
        explicit ModuleTable(const ast::nodes::Program& program);
    private:
        std::unordered_map<Symbol*, ClassInfo*> classesTable;
    };
}