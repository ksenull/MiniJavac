#pragma once

#include "../tree/Statements.h"

namespace ir {
    namespace tree {
        class IJumpBlockScheduler {
        public:
            virtual CStatementList schedule(const CStatementList &statements) = 0;
        };

        class CNaiveJumpBlockScheduler : public IJumpBlockScheduler {
        public:
            CStatementList schedule(const CStatementList &statements);
        };

    } //tree
} //ir
