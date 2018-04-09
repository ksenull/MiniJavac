#pragma once

namespace ast {

    namespace nodes {
        class Identifier;
        
        class Program;
        class MainClass;

        class ClassDeclaration;
        class ClassDeclarationList;

        class VariableDeclarationStatementList;
        class VariableDeclarationStatement;
        class VariableDeclaration;

        class Type;

        class MethodDeclarationList;
        class MethodDeclaration;

        class ArgumentDeclarationList;

        class StatementList;
        class NestedStatement;
        class IfStatement;
        class WhileStatement;
        class PrintStatement;
        class AssignStatement;
        class ArrayAssignStatement;

        class ArgumentsList;

        class BinopExpression;
        class ArrayItemExpression;
        class ArrayLengthExpression;
        class CallExpression;
        class ConstExpression;
        class BoolExpression;
        class IdExpression;
        class NewArrayExpression;
        class NewObjectExpression;
        class NotExpression;
    }


    template<typename T>
    class IVisitor {
    public:

#define DECLARE_IVISIT(NODE) virtual T visit(const nodes::NODE* node) const = 0;

    DECLARE_IVISIT(Identifier)
    DECLARE_IVISIT(Program)
    DECLARE_IVISIT(MainClass)

    DECLARE_IVISIT(ClassDeclaration)
    DECLARE_IVISIT(ClassDeclarationList)

    DECLARE_IVISIT(VariableDeclarationStatementList)
    DECLARE_IVISIT(VariableDeclarationStatement)
    DECLARE_IVISIT(VariableDeclaration)

    DECLARE_IVISIT(Type)

    DECLARE_IVISIT(MethodDeclarationList)
    DECLARE_IVISIT(MethodDeclaration)

    DECLARE_IVISIT(ArgumentDeclarationList)

    DECLARE_IVISIT(StatementList)
    DECLARE_IVISIT(NestedStatement)
    DECLARE_IVISIT(IfStatement)
    DECLARE_IVISIT(WhileStatement)
    DECLARE_IVISIT(PrintStatement)
    DECLARE_IVISIT(AssignStatement)
    DECLARE_IVISIT(ArrayAssignStatement)

    DECLARE_IVISIT(ArgumentsList)

    DECLARE_IVISIT(BinopExpression)
    DECLARE_IVISIT(ArrayItemExpression)
    DECLARE_IVISIT(ArrayLengthExpression)
    DECLARE_IVISIT(CallExpression)
    DECLARE_IVISIT(ConstExpression)
    DECLARE_IVISIT(BoolExpression)
    DECLARE_IVISIT(IdExpression)
    DECLARE_IVISIT(NewArrayExpression)
    DECLARE_IVISIT(NewObjectExpression)
    DECLARE_IVISIT(NotExpression)


#undef DECLARE_IVISIT
    };
}
