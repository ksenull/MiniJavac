#pragma once

#include <unordered_map>
#include "VariableInfo.h"

namespace symboltable {
    class MethodInfo : public IInfo {
    public:
        explicit MethodInfo(const common::Location& loc) : IInfo(loc) {}
        void BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration);
    private:
        std::unordered_map<Symbol*, VariableInfo*> vars;
        ast::nodes::Type* returnType{};
    };
}