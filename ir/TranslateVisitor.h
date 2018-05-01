#pragma once

#include "../ast/IVisitor.h"
#include "Expressions.h"

namespace ir {
    namespace translate {
        using namespace ast;

        class IRTranslateVisitor : public IVisitor<void> {
        public:
            void visit(const nodes::Identifier* node) const override;

            void visit(const nodes::Program* node) const override;

            void visit(const nodes::MainClass* node) const override;

            void visit(const nodes::ClassDeclaration* node) const override;

            void visit(const nodes::ClassDeclarationList* node) const override;

            void visit(const nodes::VariableDeclarationStatementList* node) const override;

            void visit(const nodes::VariableDeclarationStatement* node) const override;

            void visit(const nodes::VariableDeclaration* node) const override;

            void visit(const nodes::Type* node) const override;

            void visit(const nodes::MethodDeclarationList* node) const override;

            void visit(const nodes::MethodDeclaration* node) const override;

            void visit(const nodes::ArgumentDeclarationList* node) const override;

            void visit(const nodes::CStatementList* node) const override;

            void visit(const nodes::NestedStatement* node) const override;

            void visit(const nodes::IfStatement* node) const override;

            void visit(const nodes::WhileStatement* node) const override;

            void visit(const nodes::PrintStatement* node) const override;

            void visit(const nodes::AssignStatement* node) const override;

            void visit(const nodes::ArrayAssignStatement* node) const override;

            void visit(const nodes::ArgumentsList* node) const override;

            void visit(const nodes::BinopExpression* node) const override;

            void visit(const nodes::ArrayItemExpression* node) const override;

            void visit(const nodes::ArrayLengthExpression* node) const override;

            void visit(const nodes::CallExpression* node) const override;

            void visit(const nodes::ConstExpression* node) const override;

            void visit(const nodes::BoolExpression* node) const override;

            void visit(const nodes::IdExpression* node) const override;

            void visit(const nodes::NewArrayExpression* node) const override;

            void visit(const nodes::NewObjectExpression* node) const override;

            void visit(const nodes::NotExpression* node) const override;
        };

    }
}