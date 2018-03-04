//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"

#include <iostream>

namespace ast {
    void PrintVisitor::visit(const nodes::Program *program) const {
        std::cout << "[Program]\n";
    }

    void PrintVisitor::visit(const nodes::MainClass *mainClass) const {
        std::cout << "\t[MainClass]\n";
    }
}