#pragma once

#include <vector>

#include "../Temp.h"
#include "IVisitor.h"

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
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

#define DEFINE_PRINT_ACCEPT \
        void accept(const IVisitor<void>* visitor) const override { \
            visitor->visit(this); \
        }

    struct INodeList : public INode {
        INodeList() = default;

        std::vector<INode*> nodes;
    };

    struct IExpression : public INode {
        virtual ~IExpression() = default;
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct CExpressionList : INodeList {
        CExpressionList() = default;
        ~CExpressionList() = default;
        DEFINE_PRINT_ACCEPT
    };

    struct ConstExpression : IExpression {
        explicit ConstExpression(int i) : i(i) {}
        DEFINE_PRINT_ACCEPT

        int i;
    };

    struct NameExpression : IExpression {
        explicit NameExpression(const Label& label) : label(label) {}
        explicit NameExpression(const std::string& str) : label(str) {}
        DEFINE_PRINT_ACCEPT

        Label label;
    };

    struct TempExpression : IExpression {
        explicit TempExpression(IReg* reg) : reg(reg) {}
        DEFINE_PRINT_ACCEPT

        IReg* reg;
    };

    struct BinopExpression : IExpression {
        BinopExpression(IExpression* left, BinaryOperation op, IExpression* right) :
        left(left), op(op), right(right) {}
        DEFINE_PRINT_ACCEPT

        IExpression* left;
        BinaryOperation op;
        IExpression* right;
    };

    struct MemExpression : IExpression { // content of wordSize bytes from addr
        explicit MemExpression(IExpression* addr) : addr(addr) {}
        DEFINE_PRINT_ACCEPT

        IExpression* addr;
    };

    struct CallExpression : IExpression {
        CallExpression(Label* _func) : func(_func) {
            args = new CExpressionList();
        }
        CallExpression(Label* _func, CExpressionList* _args) : func(_func), args(_args) {}
        
        DEFINE_PRINT_ACCEPT

        Label* func;
        CExpressionList* args;
//        IStatement* args;
    };

    struct EseqExpression : IExpression { //stm evaluated for side effects, then e evalutes for a result
        EseqExpression(IStatement* stm, IExpression* exp) : stm(stm), exp(exp) {}
        DEFINE_PRINT_ACCEPT

        IStatement* stm;
        IExpression* exp;
    };

#undef DEFINE_PRINT_ACCEPT
}
}