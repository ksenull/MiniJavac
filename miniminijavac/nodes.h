#pragma once

#include "Visitor.h"
namespace ast {


    class Node {
    public:
        Node() = default;
        Node(const Node& another) = default;
        virtual ~Node() = default;
        virtual void accept(const IVisitor<void>* visitor) const = 0;
    };

#define DECLARE_PRINT_ACCEPT(ACCEPTOR) \
        void accept(const IVisitor<void>* visitor) const { \
            visitor->visit(this); \
        }


    class MainClass : Node {
    public:
        DECLARE_PRINT_ACCEPT(MainClass)
    };

    class Program : public Node {
        MainClass* mainClass;

    public:
        Program(MainClass* _mainClass) : mainClass(_mainClass){}
        Program(const Program& another) {
            mainClass = another.getMainClass();
        }
        ~Program() override {
            if (mainClass) delete(mainClass);
        }

        MainClass* getMainClass() const {
            return mainClass;
        }

        DECLARE_PRINT_ACCEPT(Program)
    };
}