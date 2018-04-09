//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"
#include "nodes/Nodes.h"

#include <iostream>

namespace ast {
    void PrintVisitor::visit(const nodes::Identifier* id) const {
        std::cout << "[Id " + id->getName() + "]" << std::endl;
    }
    
    void PrintVisitor::visit(const nodes::Program* program) const {
        std::cout << "[Program]" << std::endl;
    }

    void PrintVisitor::visit(const nodes::MainClass* mainClass) const {
        std::cout << "\t[MainClass]" << std::endl;
    }

    void PrintVisitor::visit(const nodes::ClassDeclaration* node) const {

    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {

    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {

    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {

    }

    void PrintVisitor::visit(const nodes::Type* node) const {

    }

    void PrintVisitor::visit(const nodes::MethodDeclarationList* node) const {

    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {

    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {

    }

    void PrintVisitor::visit(const nodes::StatementList* node) const {

    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {

    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {

    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {

    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {

    }


}