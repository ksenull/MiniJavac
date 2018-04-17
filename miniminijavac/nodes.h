#pragma once

#include <memory>
#include <vector>
#include "Visitor.h"
namespace ast {

    struct INode {
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct INodeList : INode {
        std::vector<INode*> nodes;
    };


    struct IStatement : INode {
//        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

    struct PrintStatement : IStatement {
        PrintStatement() = default;
        void accept(const IVisitor<void>* visitor) const {
            visitor->visit(this);
        }
    };
    
    struct  ReturnStatement : IStatement {
        ReturnStatement() = default;
        
        void accept(const IVisitor<void>* visitor) const {
            visitor->visit(this);
        }
    };

    struct CStatementList : INodeList {
        void accept(const IVisitor<void>* visitor) const {
            visitor->visit(this);
        }
    };

    struct MainClass : INode  {
        CStatementList* statement;
        MainClass() = default;
        explicit MainClass(CStatementList* printStatement1) : statement(printStatement1) {}

        void accept(const IVisitor<void>* visitor) const {
            visitor->visit(this);
        }
    };
    struct Program {
        MainClass* mainClass;
        Program() = default;

        explicit Program(MainClass* mainClass1) : mainClass(mainClass1) {};

        void accept(const IVisitor<void>* visitor) const {
            visitor->visit(this);
        }
    };
}