#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {

        class Expression : public Node {

        };

        class ExpressionList : public Node, NodeList {

        };


        class BinaryExpression : public Expression {
            Expression* left;
            Expression* right;
        public:
            BinaryExpression(Expression* _left, Expression* _right) : left(_left), right(_right) {}

        };


#define DEFINE_BINARY_EXP(NAME) \
        class NAME : public BinaryExpression { \
        public: \
            NAME(Expression* _left, Expression* _right) : BinaryExpression(_left, _right) {} \
            DECLARE_PRINT_ACCEPT(NAME) \
        };

        DEFINE_BINARY_EXP(And)
        DEFINE_BINARY_EXP(Less)
        DEFINE_BINARY_EXP(Plus)
        DEFINE_BINARY_EXP(Minus)
        DEFINE_BINARY_EXP(Mult)

#undef DEFINE_BINARY_EXP

        class GetItem : Expression {
            Expression* from;
            Expression* idx;
        public:
            GetItem(Expression* _from, Expression* _idx) : from(_from), idx(_idx) {}

            DECLARE_PRINT_ACCEPT(GetItem)
        };

        class Length : Expression {
            Expression* exp;
        public:
            Length(Expression* _exp) : exp(_exp) {}

            DECLARE_PRINT_ACCEPT(Length)
        };


        class MethodCall : Expression {
            Expression* obj;
            Identifier* methodId;
            ExpressionList* argList;
        public:
            MethodCall(Expression* _obj, Identifier* _methodId, ExpressionList* _args) :
                    obj(_obj), methodId(_methodId), argList(_args) {}

            DECLARE_PRINT_ACCEPT(MethodCall)
        };


        class Integral : Expression {
            int num;
        public:
            Integral(int _num) : num(_num) {}

            DECLARE_PRINT_ACCEPT(Intergral)
        };


        class Boolean : Expression {
            bool exp;
        public:
            Boolean(bool _exp) : exp(_exp) {}

            DECLARE_PRINT_ACCEPT(Boolean)
        };


        class IdExp : Expression {
            Identifier* id;
        public:
            IdExp(Identifier* _id) : id(_id) {};

            DECLARE_PRINT_ACCEPT(IdExp)
        };


        class This : Expression {
        public:
            DECLARE_PRINT_ACCEPT(This)
        };


        class NewArray : Expression {
            Expression* exp;
        public:
            NewArray(Expression* _exp) : exp(_exp) {}

            DECLARE_PRINT_ACCEPT(NewArray)
        };


        class NewObj : Expression {
            Identifier* id;
        public:
            NewObj(Identifier* _id) : id(_id) {}

            DECLARE_PRINT_ACCEPT(NewObj)
        };


        class NotExp : Expression {
            Expression* exp;
        public:
            NotExp(Expression* _exp) : exp(_exp) {}

            DECLARE_PRINT_ACCEPT(NotExp)
        };

    }
}
