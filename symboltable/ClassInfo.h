#pragma once

#include "MethodInfo.h"

#include <list>
#include <unordered_map>

namespace symboltable {
    class ClassInfo : public IInfo {
    public:
        using Block = std::unordered_map<Symbol*, IInfo*>;

        explicit ClassInfo(const common::Location&)  : IInfo(loc) {};
        void BuildFromAst(ast::nodes::MainClass*);
        void BuildFromAst(ast::nodes::ClassDeclaration*);

    private:
//        std::list<Block> scopeBlocks;
        Symbol* base{};
        std::unordered_map<Symbol*, VariableInfo*> vars;
        std::unordered_map<Symbol*, MethodInfo*> methods;
    };
}