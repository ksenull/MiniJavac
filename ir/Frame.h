#pragma once

#include <map>
#include "../symboltable/Symbol.h"
#include "../symboltable/Table.h"
#include "Access.h"
#include "ITypeSpec.h"

namespace ir {

    struct IFrame {
        IFrame() = default;
        virtual ~IFrame() = default;

        virtual void AddFormal(Label* varName, const symboltable::VariableInfo& var) = 0;
        virtual void AddLocal(Label* varName, const symboltable::VariableInfo& var) = 0;
        virtual int FormalsCount() const = 0;
        virtual const IAccess* Formal(int index) const = 0;
        virtual const IAccess* FindLocalOrFormal(Label* name) const = 0;

        virtual tree::IExpression* FramePointer() const = 0;
        virtual tree::IExpression* StackPointer() const = 0;
        virtual const IAccess* ReturnAddress() const = 0;
        virtual const IAccess* ReturnValue() const = 0;

        virtual void AddReturnAddress() = 0;
        virtual void AddReturnType(const symboltable::TypeInfo&) = 0;
        virtual void PrettyPrint() const = 0;

        virtual tree::IExpression* ExternalCall(const std::string& functionName, tree::CExpressionList* args) const = 0;

        virtual unsigned GetWordSize() const = 0;
    };

    struct Frame : public IFrame {
        Frame(symboltable::Table* table, symboltable::ClassInfo* classInfo,
              symboltable::MethodInfo* methodInfo) : table(table), classInfo(classInfo), methodInfo(methodInfo) {
            FP = new SpecialReg(0);
            SP = new SpecialReg(0);
        }

        virtual void AddFormal(Label* varName, const symboltable::VariableInfo& var);

        virtual void AddLocal(Label* varName, const symboltable::VariableInfo& var);

        virtual int FormalsCount() const;

        virtual const IAccess* Formal(int index) const;

        virtual const IAccess* FindLocalOrFormal(Label* name) const;

        virtual const IAccess* ReturnAddress() const;

        virtual const IAccess* ReturnValue() const;

        virtual void AddReturnAddress();

        virtual void AddReturnType(const symboltable::TypeInfo&);

        virtual void PrettyPrint() const;

        virtual unsigned GetWordSize() const override;
        virtual tree::IExpression* ExternalCall(const std::string& functionName, tree::CExpressionList* args) const override;

        tree::IExpression* FramePointer() const override;
        tree::IExpression* StackPointer() const override;

        std::map<Label*, IAccess*> formals;
        std::map<Label*, IAccess*> locals;
        ITypeSpec* typeSpec = new DefaultTypeSpec();
        SpecialReg* SP;
        SpecialReg* FP;

        symboltable::Table* table;
        symboltable::ClassInfo* classInfo;
        symboltable::MethodInfo* methodInfo;
    };


}