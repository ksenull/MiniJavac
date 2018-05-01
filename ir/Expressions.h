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
        explicit ConstExpression(int i) : i(i) {}

        int i;
    };

    struct NameExpression : IExpression {
        explicit NameExpression(const Label& label) : label(label) {}
        explicit NameExpression(const std::string& str) : label(str) {}

        Label label;
    };

    struct TempExpressioin : IExpression {
        explicit TempExpressioin(const TempReg& reg) : reg(reg) {}

        TempReg reg;
    };

    struct BinopExpression : IExpression {
        BinopExpression(IExpression* left, BinaryOperation op, IExpression* right) :
        left(left), op(op), right(right) {}

        IExpression* left;
        BinaryOperation op;
        IExpression* right;
    };

    struct MemExpression : IExpression { // content of wordSize bytes from addr
        explicit MemExpression(IExpression* addr) : addr(addr) {}

        IExpression* addr;
    };

    struct CallExpression : IExpression {
        CallExpression(const Label& func, CExpressionList* args) : func(func), args(args) {}

        Label func;
        CExpressionList* args;
    };

    struct EseqExpression : IExpression { //stm evaluated for side effects, then e evalutes for a result
        EseqExpression(IStatement* stm, IExpression* exp) : stm(stm), exp(exp) {}

        IStatement* stm;
        IExpression* exp;
    };
}
}