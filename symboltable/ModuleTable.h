#pragma once

#include <unordered_map>
#include "ClassInfo.h"

namespace symboltable {
    class ModuleTable {
    public:
        ModuleTable() = default;
        void BuildFromAst(const ast::nodes::Program& program);
    private:
        void checkBase(ast::nodes::ClassDeclaration* node) const;
        std::unordered_map<Symbol*, ClassInfo*> classesTable;
    };
}