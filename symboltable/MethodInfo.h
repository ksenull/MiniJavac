#pragma once

#include "VariableInfo.h"

#include <vector>
namespace symboltable {
    struct MethodInfo : IInfo {
        std::vector<VariableInfo> args;
        std::vector<VariableInfo> localVars;
        ast::nodes::Type returnType;
    };
}