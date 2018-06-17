//
// Created by Kseniia on 17.06.2018.
//
#include "Codegen.h"
#include "../ir/tree/Statements.h"

namespace codegen {

    CInstructionList ICodegen::Gen(ir::IFrame* frame, const ir::tree::CStatementList& stms) {
        CInstructionList result;
        for (auto* stm : stms.nodes) {
            auto stmCode = Gen(frame, dynamic_cast<ir::tree::IStatement*>(stm));
            result.insert(result.end(), stmCode.begin(), stmCode.end());
        }
        return result;
    }
}
