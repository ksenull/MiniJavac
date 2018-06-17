#pragma once

#include <string>
#include <deque>
#include <utility>
#include "../ir/tree/Expressions.h"

namespace codegen {

    using ir::tree::CTempExpression;
    using ir::tree::CNameExpression;
    using ir::Label;
    using CTempList = std::vector<CTempExpression*>;
    using LabelList = std::vector<Label>;

    class CInstruction {
    public:
        explicit CInstruction(std::string _assem) : assem(std::move(_assem)) {}

        explicit CInstruction(
                std::string _assem,
                CTempList _dst,
                CTempList _src,
                const LabelList& _jumps,
                const Label& _label,
                bool _isMove
        )
                : assem(std::move(_assem)), dst(std::move(_dst)), src(std::move(_src)), jumps(_jumps), label(_label), isMove(_isMove) {
        }

        std::string assem;

        CTempList dst{};
        CTempList src{};
        LabelList jumps{}; // for OPER instruction
        Label label{};  // for LABEL instruction
        bool isMove{false}; // to be able to differ MOVE and OPER istructions

        std::string str() const {
            return assem;
        }
    };

    using CInstructionList = std::deque<CInstruction>;
}