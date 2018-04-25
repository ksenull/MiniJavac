#pragma once

#include "MethodInfo.h"

#include <list>
#include <unordered_map>

namespace symboltable {
    class ClassInfo : public IInfo {
    public:
        using Block = std::unordered_map<Symbol*, IInfo*>;

        ClassInfo(ast::nodes::MainClass*);
        ClassInfo(ast::nodes::ClassDeclaration*);

    private:
//        std::list<Block> scopeBlocks;
        Symbol* base;
        std::unordered_map<Symbol*, VariableInfo*> vars;
        std::unordered_map<Symbol*, MethodInfo*> methods;
    };
}