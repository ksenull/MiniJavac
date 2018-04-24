#pragma once

#include "Symbol.h"


namespace symboltable {
    struct VariableInfo : IInfo {
        Symbol id;
        ast::nodes::Type type;
    };
}