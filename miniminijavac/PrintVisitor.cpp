//
// Created by ksenull on 4/13/18.
//

#include "Visitor.h"
#include "nodes.h"

#include <iostream>

namespace ast {

    void PrintVisitor::visit(const Program* program) const {
        fout << "program -> ";
        program->getMainClass()->accept(this);
    }

    void PrintVisitor::visit(const MainClass* node) const {
        fout << "mainClass;" << std::endl;
    }


    PrintVisitor::PrintVisitor(const std::string& filename) {
        fout.open(filename);
        fout << "digraph G {" << std::endl;
    }


    void PrintVisitor::finish() {
        fout << "}" << std::endl;
        fout.close();
    }
}