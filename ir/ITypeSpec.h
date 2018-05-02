#pragma once

#include "../symboltable/VariableInfo.h"
namespace ir {

    struct ITypeSpec {
        virtual ~ITypeSpec() {}

        virtual int getTypeSize(symboltable::VariableType type) const = 0;
        virtual int getRefSize() const = 0;
        virtual int getWordSize() const = 0;
    };

    struct DefaultTypeSpec : public ITypeSpec {
        ~DefaultTypeSpec() override = default;

        int getTypeSize(symboltable::VariableType type) const override;
        int getRefSize() const override;
        int getWordSize() const override;
    };
}