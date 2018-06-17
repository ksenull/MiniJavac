#pragma once

#include "Instruction.h"
#include "../ir/Frame.h"

namespace codegen {

    class ICodegen {
    public:
        virtual ~ICodegen() = default;
        virtual CInstructionList Gen(ir::IFrame*, ir::tree::IStatement*) = 0;
        virtual CInstructionList Gen(ir::IFrame*, const ir::tree::CStatementList&);
    };
}