#pragma once

#include "../../ast/IVisitor.h"
#include "../IFrame.h"

namespace ir {
    namespace translate {
       namespace AN = ast::nodes;

        class ISubtreeWrapper;

        class IRTranslateVisitor : public ast::IVisitor<ISubtreeWrapper*> {
        public:
            IRTranslateVisitor(IFrame* frame) : frame(frame) {}
            
            ISubtreeWrapper* visit(const AN::Identifier* node) const override;

            ISubtreeWrapper* visit(const AN::Program* node) const override;

            ISubtreeWrapper* visit(const AN::MainClass* node) const override;

            ISubtreeWrapper* visit(const AN::ClassDeclaration* node) const override;

            ISubtreeWrapper* visit(const AN::ClassDeclarationList* node) const override;

            ISubtreeWrapper* visit(const AN::VariableDeclarationStatementList* node) const override;

            ISubtreeWrapper* visit(const AN::VariableDeclarationStatement* node) const override;

            ISubtreeWrapper* visit(const AN::VariableDeclaration* node) const override;

            ISubtreeWrapper* visit(const AN::Type* node) const override;

            ISubtreeWrapper* visit(const AN::MethodDeclarationList* node) const override;

            ISubtreeWrapper* visit(const AN::MethodDeclaration* node) const override;

            ISubtreeWrapper* visit(const AN::ArgumentDeclarationList* node) const override;

            ISubtreeWrapper* visit(const AN::CStatementList* node) const override;

            ISubtreeWrapper* visit(const AN::NestedStatement* node) const override;

            ISubtreeWrapper* visit(const AN::IfStatement* node) const override;

            ISubtreeWrapper* visit(const AN::WhileStatement* node) const override;

            ISubtreeWrapper* visit(const AN::PrintStatement* node) const override;

            ISubtreeWrapper* visit(const AN::AssignStatement* node) const override;

            ISubtreeWrapper* visit(const AN::ArrayAssignStatement* node) const override;

            ISubtreeWrapper* visit(const AN::ArgumentsList* node) const override;

            ISubtreeWrapper* visit(const AN::BinopExpression* node) const override;

            ISubtreeWrapper* visit(const AN::ArrayItemExpression* node) const override;

            ISubtreeWrapper* visit(const AN::ArrayLengthExpression* node) const override;

            ISubtreeWrapper* visit(const AN::CallExpression* node) const override;

            ISubtreeWrapper* visit(const AN::ConstExpression* node) const override;

            ISubtreeWrapper* visit(const AN::BoolExpression* node) const override;

            ISubtreeWrapper* visit(const AN::IdExpression* node) const override;

            ISubtreeWrapper* visit(const AN::NewArrayExpression* node) const override;

            ISubtreeWrapper* visit(const AN::NewObjectExpression* node) const override;

            ISubtreeWrapper* visit(const AN::NotExpression* node) const override;

        private:
            IFrame* frame{};
        };

    }
}