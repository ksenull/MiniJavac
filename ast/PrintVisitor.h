#pragma once


#include <fstream>
#include "IVisitor.h"

namespace ast {

    class PrintVisitor : public  IVisitor<void> {
    public:
        PrintVisitor() = default;

        explicit PrintVisitor(const std::string& fout);
        ~PrintVisitor() = default;

        void finish();

#define DECLARE_PRINT_VISIT(NODE)  void visit(const nodes::NODE* node) const;

       DECLARE_PRINT_VISIT(Identifier)
        
        DECLARE_PRINT_VISIT(Program)
        DECLARE_PRINT_VISIT(MainClass)

        DECLARE_PRINT_VISIT(ClassDeclaration)
        DECLARE_PRINT_VISIT(ClassDeclarationList)

        DECLARE_PRINT_VISIT(VariableDeclarationStatementList)
        DECLARE_PRINT_VISIT(VariableDeclarationStatement)
        DECLARE_PRINT_VISIT(VariableDeclaration)

        DECLARE_PRINT_VISIT(Type)

        DECLARE_PRINT_VISIT(MethodDeclarationList)
        DECLARE_PRINT_VISIT(MethodDeclaration)

        DECLARE_PRINT_VISIT(ArgumentDeclarationList)

        DECLARE_PRINT_VISIT(StatementList)
        DECLARE_PRINT_VISIT(NestedStatement)
        DECLARE_PRINT_VISIT(IfStatement)
        DECLARE_PRINT_VISIT(WhileStatement)
        DECLARE_PRINT_VISIT(PrintStatement)
        DECLARE_PRINT_VISIT(AssignStatement)
        DECLARE_PRINT_VISIT(ArrayAssignStatement)

        DECLARE_PRINT_VISIT(ArgumentsList)

        DECLARE_PRINT_VISIT(BinopExpression)
        DECLARE_PRINT_VISIT(ArrayItemExpression)
        DECLARE_PRINT_VISIT(ArrayLengthExpression)
        DECLARE_PRINT_VISIT(CallExpression)
        DECLARE_PRINT_VISIT(ConstExpression)
        DECLARE_PRINT_VISIT(BoolExpression)
        DECLARE_PRINT_VISIT(IdExpression)
        DECLARE_PRINT_VISIT(NewArrayExpression)
        DECLARE_PRINT_VISIT(NewObjectExpression)
        DECLARE_PRINT_VISIT(NotExpression)


#undef DECLARE_PRINT_VISIT
    private:
        mutable std::ofstream fout;
    };


 }