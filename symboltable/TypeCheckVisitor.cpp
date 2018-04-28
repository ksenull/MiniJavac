//
// Created by ksenull on 4/28/18.
//


#include <iostream>
#include <set>

#include "TypeCheckVisitor.h"
#include "SymbolException.h"

namespace symboltable {


    void TypeCheckVisitor::visit(const ast::nodes::Identifier* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::Program* node) const {
        node->mainClass->accept(this);
        node->classDeclarationList->accept(this);
    }

    void TypeCheckVisitor::visit(const ast::nodes::MainClass* node) const {
        node->st->accept(this);
    }

    void TypeCheckVisitor::visit(const ast::nodes::ClassDeclaration* node) const {
        checkCyclicClasses(node);
    }

    void TypeCheckVisitor::visit(const ast::nodes::ClassDeclarationList* node) const {
        for (auto&& c : node->nodes) {
            c->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const ast::nodes::VariableDeclarationStatementList* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::VariableDeclarationStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::VariableDeclaration* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::Type* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::MethodDeclarationList* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::MethodDeclaration* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ArgumentDeclarationList* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::CStatementList* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::NestedStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::IfStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::WhileStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::PrintStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::AssignStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ArrayAssignStatement* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ArgumentsList* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::BinopExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ArrayItemExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ArrayLengthExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::CallExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::ConstExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::BoolExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::IdExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::NewArrayExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::NewObjectExpression* node) const {

    }

    void TypeCheckVisitor::visit(const ast::nodes::NotExpression* node) const {

    }

    void TypeCheckVisitor::checkCyclicClasses(const ast::nodes::ClassDeclaration* classDeclaration) const {
        Symbol* baseSymbol = getIntern(classDeclaration->base.name);

        std::set<Symbol*> visited;

        while (not baseSymbol->name.empty()) {
            auto* baseInfo = symbolTable.getClassInfo(baseSymbol);
            if (baseInfo == nullptr) {
                return;
            }

            if (visited.find(baseSymbol) != visited.end()) {
                throw CyclicInheritanceError(baseSymbol, baseInfo->loc, classDeclaration->loc);
            }
            visited.emplace(baseSymbol);

            if (auto* base = baseInfo->getBase()) {
                baseSymbol = getIntern(base->name);
            }
        }
    }
}
