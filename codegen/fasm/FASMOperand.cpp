#include "FASMOperand.h"
#include "FASMInstruction.h"
#include <cassert>

namespace codegen {
    namespace fasm {

        void CConstOperand::Use(CInstruction& instr, OperandUsage usage) const {
            assert(usage == ReadUsage);
            instr.assem += value;
        }

        ILoadedOperand* CConstOperand::ToLoadedOperand(CInstructionList&) const {
            return new CConstOperand(value);
        }


        std::string CInRegisterOperand::Prefix(bool asSource) {
            return asSource ? "'s" : "'d";
        }

        void CInRegisterOperand::Use(CInstruction& instruction, OperandUsage usage) const {
            bool asSource = !(usage & WriteUsage);
            auto& list = (asSource) ? instruction.src : instruction.dst;
            auto id = list.size();
            list.emplace_back(temp);
            if (usage == ReadWriteUsage) {
                instruction.src.emplace_back(temp);
            }
            instruction.assem += std::to_string(id);
        }

        ILoadedOperand* CInRegisterOperand::ToLoadedOperand(CInstructionList&) const {
            return new CInRegisterOperand(temp);
        }


        void CInMemoryOperand::Use(CInstruction& instr, OperandUsage) const {
            instr.assem += "dword[";
            addr->Use(instr, ReadUsage);
            if (offset >= 0) {
                instr.assem += '+';
            }
            instr.assem += std::to_string(offset);
            instr.assem += ']';
        }

        ILoadedOperand* CInMemoryOperand::ToLoadedOperand(CInstructionList& side) const {
            auto result = new CInRegisterOperand();
            AddMoveInstruction(*result, *this, side);
            return result;
        }


    }
}