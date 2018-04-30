#pragma once

#include "../ITypeSpec.h"

namespace ir {
    class X86MiniJavaTypeSpec : public ITypeSpec {
    public:
        int getTypeSize(ST::VariableType type) const override;
        int getRefSize() const override;
    };
}