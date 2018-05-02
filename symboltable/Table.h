#pragma once

#include <unordered_map>
#include "ClassInfo.h"

namespace symboltable {
    class Table {
    public:
        Table() = default;
        ~Table();
        void BuildFromAst(const ast::nodes::Program* program);

        ClassInfo* getClassInfo(Symbol* classSymbol) const;

        const std::unordered_map<Symbol*, ClassInfo*>& getClassesTable() const;
    private:
        void checkBase(ast::nodes::ClassDeclaration* node) const;
        std::unordered_map<Symbol*, ClassInfo*> classesTable;
    };
}