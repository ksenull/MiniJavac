#pragma once

#include "VariableInfo.h"

#include <vector>
namespace symboltable {
    struct MethodInfo : IInfo {

        explicit MethodInfo(const common::Location& loc) : IInfo(loc) {}
        void BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration);
//        std::vector<VariableInfo> args;
//        std::vector<VariableInfo> localVars;
//        ast::nodes::Type returnType;
    };
}