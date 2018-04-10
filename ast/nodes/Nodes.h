#pragma once

#include <iostream>
#include <utility>

#include "Node.h"

namespace ast {
    namespace nodes {

        class Identifier : public Node {
            std::string name;

        public:
            Identifier() = default;
            Identifier(std::string&& _name) : name(std::move(_name)) {}
            Identifier(const char* _name) : name(_name) {}
            ~Identifier() = default;

            DECLARE_PRINT_ACCEPT(Identifier)

            const std::string& getName() const;
        };

        enum TypeType {
            TT_Array,
            TT_Bool,
            TT_Int,
            TT_Object
        };
        class Type : public Node {
            Identifier id;
            TypeType tt;
        public:
            Type(const TypeType& _tt, const Identifier& _id) : tt(_tt), id(_id) {}
            explicit Type(const TypeType& _tt) : Type(_tt, Identifier{}){}
            ~Type() = default;

            DECLARE_PRINT_ACCEPT(Type)

            const std::string& get() const;
        };

        class Expression : public Node {
        };

        class ExpressionList : public Node, NodeList {
        };

        class Statement : public Node {
        };

        class StatementList : public Node, public NodeList {
        public:
            StatementList(Statement* s, StatementList* another) : NodeList(s, another) {}

            DECLARE_PRINT_ACCEPT(StatementList)
        };

        class VariableDeclaration : public Node {
            Type* type;
            Identifier id;
        public:
            VariableDeclaration(Type* _type, const Identifier& _id) : type(_type), id(_id) {}
            ~VariableDeclaration() {
                if (type) { delete(type); }
            }

            DECLARE_PRINT_ACCEPT(VariableDeclaration)
        };

        class ArgumentDeclarationList : public Node, public NodeList { // list of VariableDeclarations
        public:
            ArgumentDeclarationList(VariableDeclaration* vd, ArgumentDeclarationList* another) : NodeList(vd, another) {}

            ArgumentDeclarationList(VariableDeclaration* vd) : ArgumentDeclarationList(vd, nullptr) {}

            DECLARE_PRINT_ACCEPT(ArgumentDeclarationList)
        };

        class ArgumentsList : public Node, public NodeList{ // list of expressions
        public:
            ArgumentsList(Expression* exp, ArgumentsList* another) : NodeList(exp, another) {}
            ArgumentsList(Expression* exp) : ArgumentsList(exp, nullptr) {}
            DECLARE_PRINT_ACCEPT(ArgumentsList)
        };

        class VariableDeclarationStatement : public Statement {
            VariableDeclaration* var;
        public:
            explicit VariableDeclarationStatement(VariableDeclaration* _var) : var(_var) {}
            ~VariableDeclarationStatement() {
                if (var) delete(var);
            }

            DECLARE_PRINT_ACCEPT(VariableDeclarationStatement)
        };

        class VariableDeclarationStatementList : public Node, public NodeList {
        public:
            VariableDeclarationStatementList(VariableDeclarationStatement* vds, VariableDeclarationStatementList* vdsl) :
                    NodeList(vds, vdsl) {
                std::cout << "VariableDeclaration" <<std::endl ;
            }
            DECLARE_PRINT_ACCEPT(VariableDeclarationStatementList)
        };

        class MethodDeclaration : public Node {
            Identifier id;
            Type* returnType;
            Expression* returnExp;
            ArgumentDeclarationList* args;
            StatementList* sl;
        public:
            MethodDeclaration(const Identifier& _id, Type* _returnType, Expression* _retExp, ArgumentDeclarationList* _args, StatementList* _sl) :
                    id(_id), returnType(_returnType), returnExp(_retExp), args(_args), sl(_sl) {
                std::cout << "method declaration" << std::endl;
            }
            MethodDeclaration(const Identifier& _id, Type* _returnType, ArgumentDeclarationList* _args, StatementList* _sl) :
                    MethodDeclaration(_id, _returnType, nullptr, _args, _sl) {}
            ~MethodDeclaration() {
                if (returnType) delete(returnType);
                if (returnExp) delete(returnExp);
                if (args) delete(args);
                if (sl) delete(sl);
            }

            DECLARE_PRINT_ACCEPT(MethodDeclaration)

        };

        class MethodDeclarationList : public Node, public NodeList {
        public:
            MethodDeclarationList(MethodDeclaration* md, MethodDeclarationList* ml) : NodeList(md, ml) {}
            DECLARE_PRINT_ACCEPT(MethodDeclarationList)
        };

        class ClassDeclaration : public Node {
            Identifier id;
            Identifier base;
            VariableDeclarationStatementList* localVars;
            MethodDeclarationList* methods;
        public:

            ClassDeclaration(const Identifier& _id, const Identifier& _base,
                             VariableDeclarationStatementList* _localVars, MethodDeclarationList* _methods) :
                    id(_id), base(_base), localVars(_localVars), methods(_methods) {
                std::cout << "classDecl" <<std::endl;
            }

            ClassDeclaration(const Identifier& _id,
                             VariableDeclarationStatementList* _localVars, MethodDeclarationList* _methods) :
                    ClassDeclaration(_id, Identifier{} , _localVars, _methods) {}
            ~ClassDeclaration() {
                if (localVars) delete(localVars);
                if (methods) delete(methods);
            }

            DECLARE_PRINT_ACCEPT(ClassDeclaration)
        };

        class ClassDeclarationList : public Node, public NodeList {
        public:
            ClassDeclarationList(ClassDeclaration* cd, ClassDeclarationList* cdl) : NodeList(cd, cdl) {}

            DECLARE_PRINT_ACCEPT(ClassDeclarationList)
        };


        class MainClass : Node {
            Identifier argsName;
            Statement* st;
        public:
            MainClass(const Identifier& id, Statement* _st) : argsName(id), st(_st){}
            ~MainClass() {
                if (st) delete(st);
            }

            DECLARE_PRINT_ACCEPT(MainClass)
        };


        class Program : public Node {
            MainClass* mainClass;
            ClassDeclarationList* classDeclarationList;

        public:
            Program(MainClass* _mainClass, ClassDeclarationList* _cdl) : mainClass(_mainClass), classDeclarationList(_cdl) {}
            ~Program() {
                if (mainClass) delete(mainClass);
                if (classDeclarationList) delete(classDeclarationList);
            }

            DECLARE_PRINT_ACCEPT(Program)
        };

        class NestedStatement : public Statement {
            StatementList* sl;
        public:
            explicit NestedStatement(StatementList* _sl) : sl(_sl) {}
            ~NestedStatement() {
                if (sl) delete(sl);
            }

            DECLARE_PRINT_ACCEPT(NestedStatement)
        };

        class IfStatement : public Statement {
            Expression* condition;
            Statement* ifSt;
            Statement* elseSt;
        public:
            IfStatement(Expression* _condition, Statement* _ifSt, Statement* _elseSt) :
                    condition(_condition), ifSt(_ifSt), elseSt(_elseSt) {}
            ~IfStatement() {
                if (condition) {
                    delete(condition);
                }
                if (ifSt) delete(ifSt);
                if (elseSt) delete(elseSt);
            }

            DECLARE_PRINT_ACCEPT(IfStatement)
        };

        class WhileStatement : public Statement {
            Expression* condition;
            Statement* st;
        public:
            WhileStatement(Expression* _condition, Statement* _st) : condition(_condition), st(_st) {}
            ~WhileStatement() {
                if (condition) delete(condition);
                if (st) delete(st);
            }

            DECLARE_PRINT_ACCEPT(WhileStatement)
        };

        class PrintStatement : public Statement {
            Expression* exp;
        public:
            explicit PrintStatement(Expression* _exp) : exp(_exp) {}
            ~PrintStatement() {
                if (exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(PrintStatement)
        };

        class AssignStatement : public Statement {
            Identifier id;
            Expression* exp;
        public:
            AssignStatement(Identifier& _id, Expression* _exp) : id(_id), exp(_exp) {}
            ~AssignStatement() {
                if (exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(AssignStatement)
        };

        class ArrayAssignStatement : public Statement {
            Identifier id;
            Expression* arrExp;
            Expression* exp;
        public:
            ArrayAssignStatement(Identifier& _id, Expression* _arrExp, Expression* _exp) :
                    id(_id), arrExp(_arrExp), exp(_exp) {}
            ~ArrayAssignStatement() {
                if(arrExp) delete(arrExp);
                if(exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(ArrayAssignStatement)
        };

        enum BinOpType {
            BOT_Plus,
            BOT_Minus,
            BOT_Multiply,
            BOT_And,
            BOT_Equal,
            BOT_Less,
        };

        class BinopExpression : public Expression {
            Expression* left;
            Expression* right;
            BinOpType type;
        public:
            BinopExpression(Expression* _left, Expression* _right, const BinOpType& _type) :
                    left(_left), right(_right), type(_type) {}
            ~BinopExpression() {
                if (left) delete(left);
                if (right) delete(right);
            }

            DECLARE_PRINT_ACCEPT(BinopExpression)
        };

        class ArrayItemExpression : public Expression {
            Expression* exp;
            Expression* ind;
        public:
            ArrayItemExpression(Expression* _exp, Expression* _ind) : exp(_exp), ind(_ind) {}
            ~ArrayItemExpression() {
                if (exp) delete(exp);
                if (ind) delete(ind);
            }

            DECLARE_PRINT_ACCEPT(ArrayItemExpression)
        };

        class ArrayLengthExpression : public Expression {
            Expression* exp;
        public:
            explicit ArrayLengthExpression(Expression* _exp) : exp(_exp) {}
            ~ArrayLengthExpression() {
                if (exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(ArrayLengthExpression)
        };

        class CallExpression : public Expression {
            Expression* exp;
            Identifier method;
            ArgumentsList* args;
        public:
            CallExpression(Expression* _exp, Identifier& _method, ArgumentsList* _args) :
                    exp(_exp), method(_method), args(_args) {}
            ~CallExpression() {
                if (exp) delete(exp);
                if (args) delete(args);
            }

            DECLARE_PRINT_ACCEPT(CallExpression)
        };

        class ConstExpression : public Expression {
            int value;
        public:
            explicit ConstExpression(int _value) : value(_value) {}
            ~ConstExpression() = default;

            DECLARE_PRINT_ACCEPT(ConstExpression)
        };

        class BoolExpression : public Expression {
            bool value;
        public:
            BoolExpression(bool value) {}
            ~BoolExpression() = default;

            DECLARE_PRINT_ACCEPT(BoolExpression)
        };

        class IdExpression : public Expression {
            Identifier id;
            bool isThis;
        public:
            explicit IdExpression(const std::string& s) : isThis(true) {}
            explicit IdExpression(Identifier& _id) : id(_id) {}
            ~IdExpression() = default;

            DECLARE_PRINT_ACCEPT(IdExpression)
        };

        class NewArrayExpression : public Expression {
            Type* type;
            Expression* exp;
        public:
            NewArrayExpression(Type* _type, Expression* _exp) :
                        type(_type), exp(_exp) {}
            ~NewArrayExpression() {
                if (type) delete(type);
                if (exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(NewArrayExpression)
        };

        class NewObjectExpression : public Expression {
            Identifier id;
        public:
            explicit NewObjectExpression(Identifier& _id) : id(_id) {}
            ~NewObjectExpression() = default;

            DECLARE_PRINT_ACCEPT(NewObjectExpression)
        };

        class NotExpression : public Expression {
            Expression* exp;
        public:
            explicit NotExpression(Expression* _exp) : exp(_exp) {}
            ~NotExpression() {
                if (exp) delete(exp);
            }

            DECLARE_PRINT_ACCEPT(NotExpression)
        };
    }
}
