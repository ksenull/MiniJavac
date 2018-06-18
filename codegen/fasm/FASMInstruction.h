#pragma once

#include "../Instruction.h"

namespace codegen {
    namespace fasm {

        class IOperand;

        enum OperandUsage {
            ReadUsage = 1,
            WriteUsage = 2,
            ReadWriteUsage = ReadUsage | WriteUsage
        };

        class CInstructionBuilder {
        public:
            CInstructionBuilder& AddOperand(const IOperand& access, OperandUsage usage);

            CInstructionBuilder& DstSrc(const IOperand& access) {
                return AddOperand(access, ReadWriteUsage);
            }

            CInstructionBuilder& Dst(const IOperand& access) {
                return AddOperand(access, WriteUsage);
            }

            CInstructionBuilder& Src(const IOperand& access) {
                return AddOperand(access, ReadUsage);
            }

            CInstructionBuilder& AddJump(const Label& label) {
                instr.jumps.push_back(label);
                return *this;
            }

            operator CInstruction() const {
                return instr;
            }

        private:
            explicit CInstructionBuilder(std::string name): instr(std::move(name)) {}

            CInstruction instr;
            int operandCount = 0;

            friend CInstructionBuilder MakeInstruction(const std::string& name);
            friend CInstructionBuilder MakeLabelInstruction(Label* label);

            friend void AddMoveInstruction(const IOperand& dst, const IOperand& src, CInstructionList&);
        };

        CInstructionBuilder MakeInstruction(const std::string& name);
        CInstructionBuilder MakeLabelInstruction(Label* label);

        void AddBinaryInstruction(const std::string& name, const IOperand& dst, const IOperand& src, CInstructionList&, OperandUsage dstUsage);

        void AddMoveInstruction(const IOperand& dst, const IOperand& src, CInstructionList&);

    }
}