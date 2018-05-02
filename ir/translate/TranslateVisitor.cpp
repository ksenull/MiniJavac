//
// Created by ksenull on 5/1/18.
//
#include "TranslateVisitor.h"
#include "../../ast/nodes/Nodes.h"
#include "../IFrame.h"

namespace ir {
    namespace translate {
        namespace IRT = tree;
        namespace AST = AN;
        namespace STable = ST;
        
        ISubtreeWrapper* getIRT(AST::ClassDeclaration* classDeclaration, AST::MethodDeclaration* methodDeclaration) {
            auto* classSymbol = STable::getIntern(classDeclaration->id.name);


            IRTranslateVisitor visitor;
            IFrame frame;
            ST::getIntern(node->id.name);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Program* node) const {
            auto* classesSubtree = node->classDeclarationList->accept(this);
            auto* mainSubtree = node->mainClass->accept(this);
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MainClass* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclaration* node) const {
            auto* methodsSubtree = node->methods->accept(this);
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclarationList* node) const {
            for (auto* n : node->nodes) {
                auto* classSubtree = n->accept(this);
            }
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatementList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclaration* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Type* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclarationList* node) const {
            for (auto* n : node->nodes) {
                auto* methodSubtree = n->accept(this);
            }
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclaration* node) const {
            Symbol node->id.name
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentDeclarationList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CStatementList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NestedStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IfStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::WhileStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::PrintStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::AssignStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayAssignStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentsList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BinopExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayItemExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayLengthExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CallExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ConstExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BoolExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IdExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewArrayExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewObjectExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NotExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Identifier* node) const {
            return nullptr;
        }
        
    }
}
