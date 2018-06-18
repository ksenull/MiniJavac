#include "FASMInstruction.h"
#include "FASMOperand.h"

#include <cassert>

namespace codegen {
    namespace fasm {

        CInstructionBuilder& CInstructionBuilder::AddOperand(
                const IOperand& access, OperandUsage usage
        ) {
            if (instr.assem.length() > 4) {
                instr.assem += (operandCount++ ? ',' : '\t');
            }
            else {
                instr.assem += (operandCount++ ? "," : "\t\t");
            }
            access.Use(instr, usage);
            assert(instr.dst.size() < 2U);
            return *this;
        }

        CInstructionBuilder MakeInstruction(const std::string& name) {
            return CInstructionBuilder("\t" + name);
        }

        CInstructionBuilder MakeLabelInstruction(Label* label) {
            auto result = CInstructionBuilder{label->name + ":"};
            result.instr.label = *label;
            return result;
        }

        void AddBinaryInstruction(const std::string& name, const IOperand& dst, const IOperand& src, CInstructionList& out, OperandUsage dstUsage) {
            auto result = MakeInstruction(name).AddOperand(dst, dstUsage);
            if (dynamic_cast<const CInMemoryOperand*>(&dst) && dynamic_cast<const CInMemoryOperand*>(&src)) {
                auto tmp = src.ToLoadedOperand(out);
                result.Src(*tmp);
            } else {
                result.Src(src);
            }

            out.push_back(result);
        }

        void AddMoveInstruction(const IOperand& dst, const IOperand& src, CInstructionList& out) {
            AddBinaryInstruction("mov", dst, src, out, WriteUsage);
            out.back().isMove = (dynamic_cast<const CInRegisterOperand*>(&dst) && dynamic_cast<const CInRegisterOperand*>(&src));
        }

    }
}
