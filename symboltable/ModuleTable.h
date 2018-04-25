#pragma once

#include <unordered_map>
#include "ClassInfo.h"

namespace symboltable {
    class ModuleTable {
    public:
        explicit ModuleTable(const ast::nodes::Program& program);
    private:
        void checkBase(ast::nodes::ClassDeclaration* node) const;
        std::unordered_map<Symbol*, ClassInfo*> classesTable;
    };
}