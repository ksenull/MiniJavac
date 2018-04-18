#pragma once

#include <iostream>
#include <utility>

#include "Node.h"

namespace ast {
    namespace nodes {

        struct Identifier : INode {
            std::string name;

            Identifier() = default;

            /* implicit */ Identifier(std::string&& name) : name(std::move(name)) {}

            /* implicit */ Identifier(const char* name) : name(name) {}

            DEFINE_PRINT_ACCEPT
        };

        enum TypeType {
            TT_Array,
            TT_Bool,
            TT_Int,
            TT_Object,
            TT_Void
        };
        struct Type : INode {
            Identifier id;
            TypeType tt;

            Type(const TypeType& tt, Identifier id) : tt(tt), id(std::move(id)) {}

            explicit Type(const TypeType& tt) : Type(tt, Identifier{}){}

            DEFINE_PRINT_ACCEPT

            const std::string& get() const;
        };

        struct CExpressionList : INodeList {
            DEFINE_PRINT_ACCEPT
        };

        struct CStatementList : INodeList {
            DEFINE_PRINT_ACCEPT
        };

        struct VariableDeclaration : INode {
            Type* type;
            Identifier id;
            VariableDeclaration(Type* type, Identifier id) : type(type), id(std::move(id)) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArgumentDeclarationList : INodeList { // list of VariableDeclarations
            DEFINE_PRINT_ACCEPT
        };

        struct ArgumentsList : INodeList { // list of expressions
            DEFINE_PRINT_ACCEPT
        };

        struct VariableDeclarationStatement : IStatement {
            VariableDeclaration* var;

            explicit VariableDeclarationStatement(VariableDeclaration* var) : var(var) {}

            DEFINE_PRINT_ACCEPT
        };

        struct VariableDeclarationStatementList : INodeList { //TODO нельзя  ли заменить на statemetntsList
        public:
            DEFINE_PRINT_ACCEPT
        };

        struct MethodDeclaration : INode {
            Identifier id;
            Type* returnType;
            IExpression* returnExp;
            ArgumentDeclarationList* args;
            CStatementList* statementList;
        public:
            MethodDeclaration(const Identifier& id, Type* returnType,
                              IExpression* retExp, ArgumentDeclarationList* args, CStatementList* statementList1) :
                    id(id), returnType(returnType), returnExp(retExp), args(args), statementList(statementList1) {}
            MethodDeclaration(const Identifier& id, Type* returnType,
                              ArgumentDeclarationList* args, CStatementList* statementList1) :
                    MethodDeclaration(id, returnType , nullptr, args, statementList1) {}

            DEFINE_PRINT_ACCEPT

        };

        struct MethodDeclarationList : INodeList {
            DEFINE_PRINT_ACCEPT
        };

        struct ClassDeclaration : INode {
            Identifier id;
            Identifier base;
            VariableDeclarationStatementList* localVars;
            MethodDeclarationList* methods;

            ClassDeclaration(const Identifier& id, const Identifier& base,
                             VariableDeclarationStatementList* localVars, MethodDeclarationList* methods) :
                    id(id), base(base), localVars(localVars), methods(methods) {
            }

            ClassDeclaration(const Identifier& id,
                             VariableDeclarationStatementList* localVars, MethodDeclarationList* methods) :
                    ClassDeclaration(id, {}, localVars, methods) {}
            DEFINE_PRINT_ACCEPT
        };

        struct ClassDeclarationList : INodeList {
            DEFINE_PRINT_ACCEPT
        };


        struct MainClass : INode {
            Identifier argsName;
            IStatement* st;
        public:
            MainClass(const Identifier& id, IStatement* st) : argsName(id), st(st){}

            DEFINE_PRINT_ACCEPT
        };


        struct Program : INode {
            MainClass* mainClass;
            ClassDeclarationList* classDeclarationList;

            Program(MainClass* mainClass, ClassDeclarationList* cdl) : mainClass(mainClass), classDeclarationList(cdl) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NestedStatement : public IStatement {
            CStatementList* statementList;

            explicit NestedStatement(CStatementList* statementList1) : statementList(statementList1) {}

            DEFINE_PRINT_ACCEPT
        };

        struct IfStatement : IStatement {
            IExpression* condition;
            IStatement* ifStatement;
            IStatement* elseStatement;

            IfStatement(IExpression* condition, IStatement* ifStatement, IStatement* elseStatement) :
                condition(condition), ifStatement(ifStatement), elseStatement(elseStatement) {}

            DEFINE_PRINT_ACCEPT
        };

        struct WhileStatement : IStatement {
            IExpression* condition;
            IStatement* statement;

            WhileStatement(IExpression* condition, IStatement* statement) :
                    condition(condition), statement(statement) {}

            DEFINE_PRINT_ACCEPT
        };

        struct PrintStatement : IStatement {
            IExpression* exp;

            explicit PrintStatement(IExpression* exp) : exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct AssignStatement : IStatement {
            Identifier id;
            IExpression* exp;
        public:
            AssignStatement(Identifier& id, IExpression* exp) : id(id), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArrayAssignStatement : IStatement {
            Identifier id;
            IExpression* arrExp;
            IExpression* exp;

            ArrayAssignStatement(Identifier& id, IExpression* arrExp, IExpression* exp) :
                    id(id), arrExp(arrExp), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        enum BinOpType {
            BOT_Plus,
            BOT_Minus,
            BOT_Multiply,
            BOT_And,
            BOT_Equal,
            BOT_Less,
        };

        struct BinopExpression : IExpression {
            IExpression* left;
            IExpression* right;
            BinOpType type;

            BinopExpression(IExpression* left, IExpression* right, const BinOpType& type) :
                    left(left), right(right), type(type) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArrayItemExpression : IExpression {
            IExpression* arr;
            IExpression* ind;

            ArrayItemExpression(IExpression* arr, IExpression* ind) : arr(arr), ind(ind) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArrayLengthExpression : IExpression {
            IExpression* arr;

            explicit ArrayLengthExpression(IExpression* arr) : arr(arr) {}

            DEFINE_PRINT_ACCEPT
        };

        struct CallExpression : IExpression {
            IExpression* obj;
            Identifier method;
            ArgumentsList* args;

            CallExpression(IExpression* obj, Identifier& method, ArgumentsList* args) :
                    obj(obj), method(method), args(args) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ConstExpression : IExpression {
            int value;

            explicit ConstExpression(int value) : value(value) {}

            DEFINE_PRINT_ACCEPT
        };

        struct BoolExpression : IExpression {
            bool value;

            explicit BoolExpression(bool value) : value(value) {}

            DEFINE_PRINT_ACCEPT
        };

        struct IdExpression : IExpression {
            Identifier id;
            bool isThis; //TODO

            explicit IdExpression(const std::string& s) : isThis(true) {}
            explicit IdExpression(Identifier& id) : id(id) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NewArrayExpression : IExpression {
            Type* type;
            IExpression* exp;

            NewArrayExpression(Type* type, IExpression* exp) :
                        type(type), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NewObjectExpression : IExpression {
            Identifier id;

            explicit NewObjectExpression(Identifier& id) : id(id) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NotExpression : IExpression {
            IExpression* exp;
        public:
            explicit NotExpression(IExpression* exp) : exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };
    }
}
