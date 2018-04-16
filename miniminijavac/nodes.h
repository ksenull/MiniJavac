#pragma once

#include <memory>
#include "Visitor.h"
namespace ast {


    template <class T>
    struct IVisitorTarget {
        virtual ~IVisitorTarget() = default;
        virtual T accept(const IVisitor<T>& visitor) = 0;
    };

    struct INode : IVisitorTarget<void>{
    };

    struct IStatement : INode {
    };


#define DECLARE_PRINT_ACCEPT(ACCEPTOR) \
        virtual void accept(const IVisitor<void>& visitor) override { \
            visitor.visit(*this); \
        }


    struct PrintStatement : public IStatement {
        DECLARE_PRINT_ACCEPT(PrintStatement)
        PrintStatement() = default;
        PrintStatement(PrintStatement* another) {};
    };

    struct MainClass : public INode {
        std::shared_ptr<IStatement> st;

        MainClass(std::shared_ptr<IStatement>& st) : st(st) {};
        MainClass(MainClass* another) {
            st = another->st;
        }
        DECLARE_PRINT_ACCEPT(MainClass)
    };

    struct Program : public INode {
        std::shared_ptr<MainClass> mainClass;

        Program() = default;
        Program(std::shared_ptr<MainClass>& _mainClass) : mainClass(_mainClass){}
        Program(Program* another) {
            mainClass = another->mainClass;
        }
        ~Program() = default;

        DECLARE_PRINT_ACCEPT(Program)
    };
}