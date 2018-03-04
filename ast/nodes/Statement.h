#pragma once

#include "Node.h"
#include "../IVisitor.h"
#include "Identifier.h"
#include "Expression.h"

namespace ast {
    namespace nodes {

        class Statement : public Node {
        };


        class StatementList : public Node, public NodeList {
        };


        class Assign : public Statement {
            Identifier* id;
            Expression* exp;
        public:
            Assign::Assign(Identifier* _id, Expression* _exp) : id(_id), exp(_exp){}

            DECLARE_ACCEPT(Assign)
        };


        class IfElse : public Statement {
            Expression* condition;
            Statement* ifSt;
            Statement* elseSt;
        public:
            IfElse::IfElse(Expression* _cond, Statement* _ifSt, Statement* _elseSt) :
                    condition(_cond), ifSt(_ifSt), elseSt(_elseSt) {}

            DEFINE_ACCEPT(IfElse)
        };


        class While : public Statement {
            Expression* condition;
            Statement* st;
        public:
            While(Expression* exp, Statement* _st) : condition(exp), st(_st) {}

            DECLARE_ACCEPT(While)
        };


        class Print : public Statement {
            Expression* exp;
        public:
            Print(Expression* _exp) : exp(_exp) {}

            DECLARE_ACCEPT(Print)
        };


        class GetItem : public Statement {
            Identifier* arr;
            Expression* idx;
            Expression* exp;
        public:
            GetItem(Identifier* _arr, Expression* _idx, Expression* _exp) :
                    arr(_arr), idx(_idx), exp(_exp) {}

            DECLARE_ACCEPT(GetItem)
        };
    }
}

