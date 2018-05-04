#pragma once

#include "MethodInfo.h"

#include <list>
#include <unordered_map>

namespace symboltable {
    class ClassInfo : public IInfo {
    public:

        explicit ClassInfo(const common::Location& loc)  : IInfo(loc) {};
        ~ClassInfo();
        void BuildFromAst(ast::nodes::MainClass*);
        void BuildFromAst(ast::nodes::ClassDeclaration*);

        Symbol* getBase() const;

        MethodInfo* getMethodInfo(Symbol* methodName) const;

        VariableInfo* getVariableInfo(Symbol* varSymbol) const;

        std::unordered_map<Symbol*, VariableInfo*> getVars() const;

        std::unordered_map<Symbol*, MethodInfo*> getMethods() const;

    private:
//        std::list<Block> scopeBlocks;
        Symbol* base;
        std::unordered_map<Symbol*, VariableInfo*> vars;
        std::unordered_map<Symbol*, MethodInfo*> methods;
    };
}