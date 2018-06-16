#pragma once

#include "../symboltable/VariableInfo.h"
namespace ir {

    struct ITypeSpec {
        virtual ~ITypeSpec() {}

        virtual unsigned getTypeSize(symboltable::VariableType type) const = 0;
        virtual unsigned getRefSize() const = 0;
        virtual unsigned getWordSize() const = 0;
    };

    struct DefaultTypeSpec : public ITypeSpec {
        ~DefaultTypeSpec() override = default;

        unsigned getTypeSize(symboltable::VariableType type) const override;
        unsigned getRefSize() const override;
        unsigned getWordSize() const override;
    };
}