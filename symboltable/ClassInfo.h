#pragma once

#include "MethodInfo.h"

namespace symboltable {
    struct ClassInfo : IInfo{
        std::vector<VariableInfo> fields;
        std::vector<MethodInfo> methods;
    };
}