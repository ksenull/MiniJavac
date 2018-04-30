#pragma once

#include "../symboltable/VariableInfo.h"
namespace ir {
    namespace ST = symboltable;

    struct ITypeSpec {
        virtual ~ITypeSpec() {}

        virtual int getTypeSize(ST::VariableType type) const = 0;
        virtual int getRefSize() const = 0;
    };
}