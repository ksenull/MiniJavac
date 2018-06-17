#pragma once

#include "../tree/Statements.h"
namespace ir {
namespace tree {
    CStatementList Linearize(IStatement* stmt);
}
}