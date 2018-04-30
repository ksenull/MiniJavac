#pragma once

#include "../ast/IVisitor.h"
#include "../ast/nodes/Nodes.h"
#include "Table.h"


namespace symboltable {
    class TypeCheckVisitor : public  ast::IVisitor<void> {
    public:
        TypeCheckVisitor(const Table& table) : symbolTable(table) {}
        ~TypeCheckVisitor() = default;

#define DECLARE_TYPECHECK_VISIT(NODE)  void visit(const ast::nodes::NODE* node) const override;

        DECLARE_TYPECHECK_VISIT(Identifier)

        DECLARE_TYPECHECK_VISIT(Program)
        DECLARE_TYPECHECK_VISIT(MainClass)

        DECLARE_TYPECHECK_VISIT(ClassDeclaration)
        DECLARE_TYPECHECK_VISIT(ClassDeclarationList)

        DECLARE_TYPECHECK_VISIT(VariableDeclarationStatementList)
        DECLARE_TYPECHECK_VISIT(VariableDeclarationStatement)
        DECLARE_TYPECHECK_VISIT(VariableDeclaration)

        DECLARE_TYPECHECK_VISIT(Type)

        DECLARE_TYPECHECK_VISIT(MethodDeclarationList)
        DECLARE_TYPECHECK_VISIT(MethodDeclaration)

        DECLARE_TYPECHECK_VISIT(ArgumentDeclarationList)

        DECLARE_TYPECHECK_VISIT(CStatementList)
        DECLARE_TYPECHECK_VISIT(NestedStatement)
        DECLARE_TYPECHECK_VISIT(IfStatement)
        DECLARE_TYPECHECK_VISIT(WhileStatement)
        DECLARE_TYPECHECK_VISIT(PrintStatement)
        DECLARE_TYPECHECK_VISIT(AssignStatement)
        DECLARE_TYPECHECK_VISIT(ArrayAssignStatement)

        DECLARE_TYPECHECK_VISIT(ArgumentsList)

        DECLARE_TYPECHECK_VISIT(BinopExpression)
        DECLARE_TYPECHECK_VISIT(ArrayItemExpression)
        DECLARE_TYPECHECK_VISIT(ArrayLengthExpression)
        DECLARE_TYPECHECK_VISIT(CallExpression)
        DECLARE_TYPECHECK_VISIT(ConstExpression)
        DECLARE_TYPECHECK_VISIT(BoolExpression)
        DECLARE_TYPECHECK_VISIT(IdExpression)
        DECLARE_TYPECHECK_VISIT(NewArrayExpression)
        DECLARE_TYPECHECK_VISIT(NewObjectExpression)
        DECLARE_TYPECHECK_VISIT(NotExpression)

#undef DECLARE_TYPECHECK_VISIT

    private:
        void checkCyclicClasses(const ast::nodes::ClassDeclaration* classDeclaration) const;

        void checkBooleanConvertibility(const ast::nodes::IExpression* exp) const;

        void checkIfInt(const ast::nodes::IExpression* exp) const;

//        bool areTypesDifferent(const ast::nodes::Type& type, const ast::nodes::Type& correctType) const;

//        void checkIfSameType(Symbol* left, ast::nodes::IExpression* exp) const;

        std::pair<bool, TypeInfo> getExpressionType(const ast::nodes::IExpression* exp) const;
        std::pair<bool, TypeInfo> getIdType(const ast::nodes::Identifier&) const;


        Table symbolTable;
        mutable Symbol* currentClass;
        mutable Symbol* curMethod;
    };
}