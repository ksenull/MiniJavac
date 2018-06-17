//
// Created by Kseniia on 17.06.2018.
//
#include "TraceSchedule.h"

namespace ir {
    namespace tree {
        CStatementList CNaiveJumpBlockScheduler::schedule(const CStatementList& stms) {
            CStatementList result;
            for (auto stm : stms.nodes) {
                if (auto current = dynamic_cast<CCondJumpStatement*>(stm)) {
                    result.nodes.emplace_back(stm);
                    auto* jump = new CJumpStatement(current->elseTarget);
                    result.nodes.emplace_back(jump);
                } else {
                    result.nodes.emplace_back(stm);
                }
            }
            return result;
        }
    }
}
