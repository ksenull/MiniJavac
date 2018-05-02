#pragma once

#include "../symboltable/Symbol.h"
#include "../symboltable/Table.h"
#include "Access.h"

namespace ir {

    struct IFrame {
        IFrame() = default;
        virtual ~IFrame() = default;

        virtual void AddFormal(symboltable::Symbol* varName, const symboltable::VariableInfo& var) = 0;
        virtual void AddLocal(symboltable::Symbol* varName, const symboltable::VariableInfo& var) = 0;
        virtual int FormalsCount() const = 0;
        virtual const IAccess* Formal(int index) const = 0;
        virtual const IAccess* FindLocalOrFormal(const symboltable::Symbol* name) const = 0;

        virtual TempReg& FramePointer() const = 0;
        virtual TempReg& StackPointer() const = 0;
        virtual const IAccess* ReturnAddress() const = 0;
        virtual const IAccess* ReturnValue() const = 0;

        virtual int wordSize() const = 0;

        virtual void AddReturnAddress() = 0;
        virtual void AddReturnType(const symboltable::TypeInfo&) = 0;
        virtual void PrettyPrint() const = 0;
    };

    struct Frame : public IFrame {
        Frame(symboltable::Table* table, symboltable::ClassInfo* classInfo,
              symboltable::MethodInfo* methodInfo) : table(table), classInfo(classInfo), methodInfo(methodInfo) {}

        virtual void AddFormal(symboltable::Symbol* varName, const symboltable::VariableInfo& var);
        virtual void AddLocal(symboltable::Symbol* varName, const symboltable::VariableInfo& var);
        virtual int FormalsCount() const;
        virtual const IAccess* Formal(int index) const;
        virtual const IAccess* FindLocalOrFormal(const symboltable::Symbol* name) const;

        virtual TempReg& FramePointer() const;
        virtual TempReg& StackPointer() const;
        virtual const IAccess* ReturnAddress() const;
        virtual const IAccess* ReturnValue() const;

        virtual int wordSize() const;

        virtual void AddReturnAddress();
        virtual void AddReturnType(const symboltable::TypeInfo&);
        virtual void PrettyPrint() const;

        symboltable::Table* table;
        symboltable::ClassInfo* classInfo;
        symboltable::MethodInfo* methodInfo;
    };
}