#pragma once

#include <vector>
#include "Temp.h"

namespace ir {
namespace tree {

    enum BinaryOperation {
        BO_Plus, BO_Minus, BO_Mul, BO_Div, BO_And, BO_Or, BO_Lshift, BO_Rshift, BO_Arshift, BO_Xor
    };

    enum RelationalOperation {
        RO_Eq, RO_Ne, RO_Lt, RO_Gt, RO_Le, RO_Ge, RO_Ult, RO_Ugt, RO_Ule, RO_Uge
    };

    struct IStatement;

    struct INode {
        virtual ~INode() = default;
    };

    struct INodeList : public INode {
        INodeList() = default;

        std::vector<INode*> nodes;
    };

    struct IExpression {
        virtual ~IExpression() = 0;
    };

    struct CExpressionList : INodeList {
    };

    struct ConstExpression : IExpression {
        int i;
    };

    struct NameExpression : IExpression {
        Label label;
    };

    struct TempExpressioin : IExpression {
        TempReg reg;
    };

    struct BinopExpression : IExpression {
        IExpression* left;
        BinaryOperation op;
        IExpression* right;
    };

    struct MemExpression : IExpression { // content of wordSize bytes from addr
        IExpression* addr;
    };

    struct CallExpression : IExpression {
        Label func;
        CExpressionList* args;
    };

    struct EseqExpression : IExpression { //stm evaluated for side effects, then e evalutes for a result
        IStatement* stm;
        IExpression* exp;
    };
}
}