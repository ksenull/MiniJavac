//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(StatementList)
        DEFINE_PRINT_ACCEPT(NestedStatement)

        StatementList* NestedStatement::getSl() const {
            return sl;
        }

        DEFINE_PRINT_ACCEPT(IfStatement)

        Expression* IfStatement::getCondition() const {
            return condition;
        }

        Statement* IfStatement::getIfSt() const {
            return ifSt;
        }

        Statement* IfStatement::getElseSt() const {
            return elseSt;
        }

        DEFINE_PRINT_ACCEPT(WhileStatement)

        Expression* WhileStatement::getCondition() const {
            return condition;
        }

        Statement* WhileStatement::getSt() const {
            return st;
        }

        DEFINE_PRINT_ACCEPT(PrintStatement)

        Expression* PrintStatement::getExp() const {
            return exp;
        }

        DEFINE_PRINT_ACCEPT(AssignStatement)

        const Identifier& AssignStatement::getId() const {
            return id;
        }

        Expression* AssignStatement::getExp() const {
            return exp;
        }

        DEFINE_PRINT_ACCEPT(ArrayAssignStatement)

        const Identifier& ArrayAssignStatement::getId() const {
            return id;
        }

        Expression* ArrayAssignStatement::getArrExp() const {
            return arrExp;
        }

        Expression* ArrayAssignStatement::getExp() const {
            return exp;
        }
    }
}