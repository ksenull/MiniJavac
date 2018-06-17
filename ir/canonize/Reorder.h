#pragma once

#include "../tree/Statements.h"


namespace ir {
    namespace tree {
        CExpressionList* ExtractExpressions(INode* node);

        IStatement* ProcessStm(IStatement* stmt, CExpressionList* expsExtracted);

        IExpression* ProcessExp(IExpression* expr, CExpressionList* expsExtracted);
    }
}