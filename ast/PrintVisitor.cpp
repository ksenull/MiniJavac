//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"

#include <iostream>

namespace ast {
    void PrintVisitor::visit(const nodes::Program* program) const {
        std::cout << "[Program]\n";
    }

    void PrintVisitor::visit(const nodes::MainClass* mainClass) const {
        std::cout << "\t[MainClass]\n";
    }

    void PrintVisitor::visit(const nodes::Identifier* id) const {
        std::cout << "[Identifier] ";
    }

    void PrintVisitor::visit(const nodes::Assign* node) const {
        std::cout << "[Assign] \n";
    }

    void PrintVisitor::visit(const nodes::IfElse* node) const {

    }

    void PrintVisitor::visit(const nodes::While* node) const {

    }

    void PrintVisitor::visit(const nodes::Print* node) const {

    }

    void PrintVisitor::visit(const nodes::GetItem* node) const {
        
    }

    void PrintVisitor::visit(const nodes::And* node) const {

    }

    void PrintVisitor::visit(const nodes::Less* node) const {

    }

    void PrintVisitor::visit(const nodes::Plus* node) const {

    }

    void PrintVisitor::visit(const nodes::Minus* node) const {

    }

    void PrintVisitor::visit(const nodes::Mult* node) const {

    }

}