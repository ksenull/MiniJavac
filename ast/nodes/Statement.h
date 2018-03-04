#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {

        class Identifier;
        class Expression;


        class Statement : public Node {
        };


        class StatementList : public Node, public NodeList {
        };


        class Assign : public Statement {
            Identifier* id;
            Expression* exp;
        public:
            Assign(Identifier* _id, Expression* _exp) : id(_id), exp(_exp){}

            DECLARE_PRINT_ACCEPT(Assign)
        };


        class IfElse : public Statement {
            Expression* condition;
            Statement* ifSt;
            Statement* elseSt;
        public:
            IfElse(Expression* _cond, Statement* _ifSt, Statement* _elseSt) :
                    condition(_cond), ifSt(_ifSt), elseSt(_elseSt) {}

            DECLARE_PRINT_ACCEPT(IfElse)
        };


        class While : public Statement {
            Expression* condition;
            Statement* st;
        public:
            While(Expression* exp, Statement* _st) : condition(exp), st(_st) {}

            DECLARE_PRINT_ACCEPT(While)
        };


        class Print : public Statement {
            Expression* exp;
        public:
            Print(Expression* _exp) : exp(_exp) {}

            DECLARE_PRINT_ACCEPT(Print)
        };


        class GetItem : public Statement {
            Identifier* arr;
            Expression* idx;
            Expression* exp;
        public:
            GetItem(Identifier* _arr, Expression* _idx, Expression* _exp) :
                    arr(_arr), idx(_idx), exp(_exp) {}

            DECLARE_PRINT_ACCEPT(GetItem)
        };
    }
}

