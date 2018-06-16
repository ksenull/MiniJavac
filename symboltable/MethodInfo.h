#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include "VariableInfo.h"

namespace symboltable {
    class MethodInfo : public IInfo {
    public:
        using ArgsList = std::vector<std::pair<Symbol*, VariableInfo*>>;

        explicit MethodInfo(std::unordered_map<Symbol*, VariableInfo*> classVars, const common::Location& loc) : IInfo(loc) {
            for (auto&& classVar : classVars) {
                vars.emplace(classVar);
            }
        }
        
        void BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration);
        void BuildFromAst(ast::nodes::MainClass* main);

        ArgsList getArgsList();
        ArgsList getLocalVarsList();
        TypeInfo getReturnType() const;

        VariableInfo* getVariableInfo(Symbol* varSymbol) const;
    private:
        ArgsList args;
        ArgsList localVars;
        std::unordered_map<Symbol*, VariableInfo*> vars;
        TypeInfo returnType{};
    };
}