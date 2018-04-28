#pragma once

#include "MethodInfo.h"

#include <list>
#include <unordered_map>

namespace symboltable {
    class ClassInfo : public IInfo {
    public:

        explicit ClassInfo(const common::Location&)  : IInfo(loc) {};
        ~ClassInfo();
        void BuildFromAst(ast::nodes::MainClass*);
        void BuildFromAst(ast::nodes::ClassDeclaration*);

        Symbol* getBase() const;

    private:
//        std::list<Block> scopeBlocks;
        Symbol* base{};
        std::unordered_map<Symbol*, VariableInfo*> vars;
        std::unordered_map<Symbol*, MethodInfo*> methods;
    };
}