#pragma once

#include <map>
#include "../IFrame.h"
#include "X86TypeSpec.h"

namespace ir {

    using Symbol = ST::Symbol;

    struct CX86MiniJavaFrame : public IFrame {
    public:
        CX86MiniJavaFrame(ITypeSpec* typeSpec, int sp, int fp) : typeSpec(typeSpec), stackPointer(sp), framePointer(fp) {}

        void AddFormal(ST::Symbol* varName, const ST::VariableInfo& var) override;

        void AddLocal(ST::Symbol* varName, const ST::VariableInfo& var) override;

        int FormalsCount() const override;

        const IAccess* Formal(int index) const override;

        const IAccess* FindLocalOrFormal(const ST::Symbol* name) const override;

        int FramePointer() const override;

        int StackPointer() const override;

        const IAccess* ReturnAddress() const override;

        const IAccess* ReturnValue() const override;

        void AddReturnAddress() override;

        void AddReturnType(const ST::TypeInfo& info) override;

        void PrettyPrint() const;

    private:
        int stackPointer;
        int framePointer;

        std::vector<IAccess*> formalsList;

        std::map<const Symbol*, IAccess*> formals;
        std::map<const Symbol*, IAccess*> locals;

        IAccess* returnAddress;
        IAccess* returnValue;

        ITypeSpec* typeSpec;
    };
}