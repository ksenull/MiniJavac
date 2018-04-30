#pragma once

#include "../symboltable/Symbol.h"
#include "Access.h"
#include "../symboltable/VariableInfo.h"

namespace frames {
    namespace ST = symboltable;

    struct IFrame {
        virtual void AddFormal(ST::Symbol* varName, const ST::VariableInfo& var) = 0;
        virtual void AddLocal(ST::Symbol* varName, const ST::VariableInfo& var) = 0;
        virtual int FormalsCount() const = 0;
        virtual const IAccess* Formal(int index) const = 0;
        virtual const IAccess* FindLocalOrFormal(const ST::Symbol* name) const = 0;

        virtual const Temp FramePointer() const = 0;
        virtual const Temp StackPointer() const = 0;
        virtual const IAccess* ReturnAddress() const = 0;
        virtual const IAccess* ReturnValue() const = 0;

        virtual void AddReturnAddress() = 0;
        virtual void AddReturnType(const ST::TypeInfo&) = 0;
        virtual void PrettyPrint() const = 0;

    };
}