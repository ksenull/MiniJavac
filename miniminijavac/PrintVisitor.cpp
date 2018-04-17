//
// Created by ksenull on 4/13/18.
//

#include "Visitor.h"
#include "nodes.h"

#include <iostream>

namespace ast {

    void PrintVisitor::visit(const Program* program) const {
        fout << "program -> ";
//        std::cout << program.mainClass;
        program->mainClass->accept(this);
    }

    void PrintVisitor::visit(const MainClass* node) const {
        fout << "mainClass -> ";
        node->statement->accept(this);
    }

    void PrintVisitor::visit(const CStatementList* statementList) const {
        fout << "statementList;" << std::endl;
        for (auto&& st : statementList->nodes) {
            fout << "statementList -> ";
            st->accept(this);
        }
    }
    void PrintVisitor::visit(const PrintStatement* printSt) const {
        fout << "printStatement;" << std::endl;
    }

    void PrintVisitor::visit(const ReturnStatement* printSt) const {
        fout << "returnStatement;" << std::endl;
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