#pragma once

#include "FASMInstruction.h"
#include <string>


namespace codegen {
    namespace fasm {

        class ILoadedOperand;

        class IOperand {
        public:
            virtual void Use(CInstruction&, OperandUsage usage) const = 0;
            virtual ILoadedOperand* ToLoadedOperand(CInstructionList&) const = 0;
        };

        class ILoadedOperand : public IOperand {};

        struct CConstOperand : public ILoadedOperand {
            explicit CConstOperand(int _value) : value(std::to_string(_value)) {}
            explicit CConstOperand(Label* _value) : value(_value->name) {}
            explicit CConstOperand(std::string _value) : value(std::move(_value)) {}

            void Use(CInstruction&, OperandUsage usage) const override;
            ILoadedOperand* ToLoadedOperand(CInstructionList& side) const override;

            std::string value;
        };

        struct CInRegisterOperand : public ILoadedOperand {
            explicit CInRegisterOperand() : temp(new CTempExpression(new ir::TempReg())) {}
            explicit CInRegisterOperand(CTempExpression* _temp) : temp(_temp) {}

            static std::string Prefix(bool asSource);

            void Use(CInstruction& instr, OperandUsage usage) const override;
            ILoadedOperand* ToLoadedOperand(CInstructionList&) const override;

            CTempExpression* temp;
        };

        struct CInMemoryOperand : public IOperand {
            explicit CInMemoryOperand(ILoadedOperand* _addr, int _offset=0) : addr(std::move(_addr)), offset(_offset) {}

            void Use(CInstruction& instr, OperandUsage) const override;
            ILoadedOperand* ToLoadedOperand(CInstructionList& side) const override;

            ILoadedOperand* addr;
            int offset;
        };

    }
}