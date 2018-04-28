#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include "VariableInfo.h"

namespace symboltable {
    class MethodInfo : public IInfo {
    public:
        using ArgsList = std::vector<std::pair<Symbol*, VariableInfo*>>;

        explicit MethodInfo(const common::Location& loc) : IInfo(loc) {}
        void BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration);

        ArgsList getArgsList();
    private:
        ArgsList args;
        std::unordered_map<Symbol*, VariableInfo*> vars;
        ast::nodes::Type* returnType{};
    };
}