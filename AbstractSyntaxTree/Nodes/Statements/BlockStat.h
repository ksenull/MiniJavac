//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_BLOCKSTAT_H
#define AST_BLOCKSTAT_H

#include <vector>
#include "../IStatement.h"
#include "../../IVisitor.h"

namespace AST {
    class BlockStatement : IStatement {
    public:
        void Accept(IVisitor* visitor) {
            visitor->visit(this);
        }
    private:
        std::vector<IStatement> statements;
    };
}
#endif //AST_BLOCKSTAT_H
