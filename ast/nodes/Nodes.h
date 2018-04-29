#pragma once

#include <iostream>
#include <utility>

#include "INode.h"
#include "Identifier.h"

namespace ast {
    namespace nodes {

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

            Type(const TypeType& tt, const Identifier& id, const Location& loc) : INode(loc), tt(tt), id(std::move(id)) {}

            explicit Type(const TypeType& tt, const Location& loc) : Type(tt, Identifier{}, loc){}

            DEFINE_PRINT_ACCEPT

            std::string getTT() const {
                switch (tt) {
                    case TT_Array:
                            return "int[]";
                    case TT_Bool:
                            return "bool";
                    case TT_Int:
                            return "int";
                    case TT_Object:
                        if (id.name.empty()) {
                            return "object";
                        }
                        else {
                            return id.name;
                        }
                    case TT_Void:
                            return "void";
                    default:
                            return "";
                }
            };
        };

//        struct CExpressionList : INodeList {
//            DEFINE_PRINT_ACCEPT
//        };

        struct CStatementList : INodeList {
            DEFINE_PRINT_ACCEPT
        };

        struct VariableDeclaration : INode {
            Type* type;
            Identifier id;
            VariableDeclaration(Type* type, const Identifier& id, const Location& loc) : INode(loc), type(type), id(std::move(id)) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArgumentDeclarationList : INodeList { // list of VariableDeclarations
            ArgumentDeclarationList() = default;
            explicit ArgumentDeclarationList(VariableDeclaration* var) {
                    nodes = {var};
            };
            DEFINE_PRINT_ACCEPT
        };

        struct ArgumentsList : INodeList { // list of expressions
            ArgumentsList() = default;
            explicit ArgumentsList(IExpression* exp) {
                    nodes = {exp};
            };
            DEFINE_PRINT_ACCEPT
        };

        struct VariableDeclarationStatement : IStatement {
            VariableDeclaration* var;

            explicit VariableDeclarationStatement(VariableDeclaration* var, const Location& loc) : IStatement(loc), var(var) {}

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

            MethodDeclaration(const Identifier& id, Type* returnType,
                              IExpression* retExp, ArgumentDeclarationList* args,
                              CStatementList* statementList1, const Location& loc) :
                    INode(loc), id(id), returnType(returnType), returnExp(retExp),
                    args(args), statementList(statementList1) {}
            MethodDeclaration(const Identifier& id, Type* returnType,
                              ArgumentDeclarationList* args, CStatementList* statementList1, const Location& loc) :
                    MethodDeclaration(id, returnType , nullptr, args, statementList1, loc) {}

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
                             VariableDeclarationStatementList* localVars,
                             MethodDeclarationList* methods, const Location& loc) :
                    INode(loc), id(id), base(base), localVars(localVars), methods(methods) {}

            ClassDeclaration(const Identifier& id,
                             VariableDeclarationStatementList* localVars,
                             MethodDeclarationList* methods, const Location& loc) :
                    ClassDeclaration(id, {}, localVars, methods, loc) {}
            DEFINE_PRINT_ACCEPT
        };

        struct ClassDeclarationList : INodeList {
            DEFINE_PRINT_ACCEPT
        };


        struct MainClass : INode {
            Identifier name;
            Identifier argsName;
            IStatement* st;
        public:
            MainClass(const Identifier& name, Identifier id, IStatement* st, const Location& loc) : INode(loc),
                    name(std::move(name)), argsName(std::move(id)), st(st) {}

            DEFINE_PRINT_ACCEPT
        };


        struct Program : INode {
            MainClass* mainClass;
            ClassDeclarationList* classDeclarationList;

            Program() = default;

            Program(MainClass* mainClass, ClassDeclarationList* cdl, const Location& loc) :
                    INode(loc), mainClass(mainClass), classDeclarationList(cdl) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NestedStatement : public IStatement {
            CStatementList* statementList;

            explicit NestedStatement(CStatementList* statementList1, const Location& loc) :
                    IStatement(loc), statementList(statementList1) {}

            DEFINE_PRINT_ACCEPT
        };

        struct IfStatement : IStatement {
            IExpression* condition;
            IStatement* ifStatement;
            IStatement* elseStatement;

            IfStatement(IExpression* condition, IStatement* ifStatement,
                        IStatement* elseStatement, const Location& loc) : IStatement(loc),
                condition(condition), ifStatement(ifStatement), elseStatement(elseStatement) {}

            DEFINE_PRINT_ACCEPT
        };

        struct WhileStatement : IStatement {
            IExpression* condition;
            IStatement* statement;

            WhileStatement(IExpression* condition, IStatement* statement,
                    const Location& loc) : IStatement(loc),
                    condition(condition), statement(statement) {}

            DEFINE_PRINT_ACCEPT
        };

        struct PrintStatement : IStatement {
            IExpression* exp;

            explicit PrintStatement(IExpression* exp, const Location& loc) : IStatement(loc), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct AssignStatement : IStatement {
            Identifier id;
            IExpression* exp;
        public:
            AssignStatement(Identifier& id, IExpression* exp, const Location& loc) : IStatement(loc), id(id), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArrayAssignStatement : IStatement {
            Identifier id;
            IExpression* arrExp;
            IExpression* exp;

            ArrayAssignStatement(Identifier& id, IExpression* arrExp, IExpression* exp, const Location& loc) :
                    IStatement(loc), id(id), arrExp(arrExp), exp(exp) {}

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

            BinopExpression(IExpression* left, IExpression* right, const BinOpType& type, const Location& loc) :
                    IExpression(loc), left(left), right(right), type(type) {}

            DEFINE_PRINT_ACCEPT

            std::string binOpTypeToStr() const {
                switch (type) {
                    case BOT_Plus:
                        return "Plus";
                    case BOT_Minus:
                        return "Minus";
                    case BOT_Multiply:
                        return "Multiply";
                    case BOT_And:
                        return "And";
                    case BOT_Equal:
                        return "Equal";
                    case BOT_Less:
                        return "Less";
                    default:
                        return "";
                }
            }
        };

        struct ArrayItemExpression : IExpression {
            IExpression* arr;
            IExpression* ind;

            ArrayItemExpression(IExpression* arr, IExpression* ind, const Location& loc) :
                    IExpression(loc), arr(arr), ind(ind) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ArrayLengthExpression : IExpression {
            IExpression* arr;

            explicit ArrayLengthExpression(IExpression* arr, const Location& loc) : IExpression(loc), arr(arr) {}

            DEFINE_PRINT_ACCEPT
        };

        struct CallExpression : IExpression {
            IExpression* obj;
            Identifier method;
            ArgumentsList* args;

            CallExpression(IExpression* obj, Identifier& method, ArgumentsList* args, const Location& loc) :
                    IExpression(loc), obj(obj), method(method), args(args) {}

            DEFINE_PRINT_ACCEPT
        };

        struct ConstExpression : IExpression {
            int value;

            explicit ConstExpression(int value, const Location& loc) : IExpression(loc), value(value) {}

            DEFINE_PRINT_ACCEPT
        };

        struct BoolExpression : IExpression {
            bool value;

            explicit BoolExpression(bool value, const Location& loc) : IExpression(loc), value(value) {}

            DEFINE_PRINT_ACCEPT
        };

        struct IdExpression : IExpression {
            Identifier id;
            bool isThis; //TODO

            explicit IdExpression(const std::string& s, const Location& loc) : IExpression(loc), isThis(true) {}
            explicit IdExpression(Identifier& id, const Location& loc) : IExpression(loc), id(id) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NewArrayExpression : IExpression {
//            Type* type;
            IExpression* exp;

            NewArrayExpression(IExpression* exp, const Location& loc) :
                        IExpression(loc), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NewObjectExpression : IExpression {
            Identifier id;

            explicit NewObjectExpression(Identifier& id, const Location& loc) : IExpression(loc), id(id) {}

            DEFINE_PRINT_ACCEPT
        };

        struct NotExpression : IExpression {
            IExpression* exp;
        public:
            explicit NotExpression(IExpression* exp, const Location& loc) : IExpression(loc), exp(exp) {}

            DEFINE_PRINT_ACCEPT
        };
    }
}
