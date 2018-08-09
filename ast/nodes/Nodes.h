#pragma once

#include <iostream>
#include <utility>
#include <memory>

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

#define DEFINE_PRINT_ACCEPT \
        void accept(const IVisitor<void>* visitor) const { \
            visitor->visit(this); \
        }

#define DEFINE_IRTRANSLATE_ACCEPT \
        ir::translate::ISubtreeWrapper* accept(const IVisitor<ir::translate::ISubtreeWrapper*>* visitor) const { \
            return visitor->visit(this); \
        }

        struct Type : INode {
            std::shared_ptr<Identifier> id;
            TypeType tt;

            Type(const TypeType& _tt, std::shared_ptr<Identifier> _id, const Location& loc)
                    : INode(loc), tt(_tt), id(std::move(_id)) {}

            explicit Type(const TypeType& _tt, const Location& _loc)
                    : Type(_tt, nullptr, _loc){}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT

            std::string getTT() const {
                switch (tt) {
                    case TT_Array:
                            return "int[]";
                    case TT_Bool:
                            return "bool";
                    case TT_Int:
                            return "int";
                    case TT_Object:
                        if (id->name.empty()) { return "object"; }
                        else { return id->name; }
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
            explicit CStatementList(const Location& _loc)
                    : INodeList(_loc) {}
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct VariableDeclaration : INode {
            std::shared_ptr<Type> type;
            std::shared_ptr<Identifier> id;
            VariableDeclaration(std::shared_ptr<Type> _type, std::shared_ptr<Identifier> _id, const Location& _loc)
                    : INode(_loc), type(std::move(_type)), id(std::move(_id)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ArgumentDeclarationList : INodeList { // list of VariableDeclarations
            explicit ArgumentDeclarationList(const Location& _loc)
                    : INodeList(_loc) {}
            ArgumentDeclarationList(std::shared_ptr<VariableDeclaration> _var, const Location& _loc) : INodeList(_loc) {
                    nodes.emplace_back(_var);
            };
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ArgumentsList : INodeList { // list of expressions
            explicit ArgumentsList(const Location& _loc)
                    : INodeList(_loc) {}
            ArgumentsList(std::shared_ptr<IExpression> _exp, const Location& _loc) : INodeList(_loc) {
                    nodes.emplace_back(_exp);
            };
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct VariableDeclarationStatement : IStatement {
            std::shared_ptr<VariableDeclaration> var;

            explicit VariableDeclarationStatement(std::shared_ptr<VariableDeclaration> _var, const Location& _loc)
                    : IStatement(_loc), var(std::move(_var)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct VariableDeclarationStatementList : INodeList { //TODO нельзя  ли заменить на statemetntsList
        public:
            explicit VariableDeclarationStatementList(const Location& _loc)
                    : INodeList(_loc) {}
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct MethodDeclaration : INode {
            std::shared_ptr<Identifier> id;
            std::shared_ptr<Type> returnType;
            std::shared_ptr<IExpression> returnExp;
            std::shared_ptr<ArgumentDeclarationList> args;
            std::shared_ptr<CStatementList> statementList;

            MethodDeclaration(
                    std::shared_ptr<Identifier> _id,
                    std::shared_ptr<Type> _returnType,
                    std::shared_ptr<IExpression> _retExp,
                    std::shared_ptr<ArgumentDeclarationList> _args,
                    std::shared_ptr<CStatementList> _statementList,
                    const Location& _loc)
                    : INode(_loc), id(std::move(_id)), returnType(std::move(_returnType)), returnExp(std::move(_retExp)),
                    args(std::move(_args)), statementList(std::move(_statementList)) {}

            MethodDeclaration(
                    std::shared_ptr<Identifier> _id,
                    std::shared_ptr<Type> _returnType,
                    std::shared_ptr<ArgumentDeclarationList> _args,
                    std::shared_ptr<CStatementList> _statementList,
                    const Location& _loc)
                    : MethodDeclaration(std::move(_id), std::move(_returnType), nullptr, _args, _statementList, _loc) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct MethodDeclarationList : INodeList {
            explicit MethodDeclarationList(const Location& _loc)
                    : INodeList(_loc) {}
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct IClassDecl : INode {
            std::shared_ptr<Identifier> id;

            IClassDecl(const Location& _loc, std::shared_ptr<Identifier> _id)
                    : INode(_loc), id(std::move(_id)) {}
        };

        struct ClassDeclaration : IClassDecl {
            std::shared_ptr<Identifier> base;
            std::shared_ptr<VariableDeclarationStatementList> localVars;
            std::shared_ptr<MethodDeclarationList> methods;

            ClassDeclaration(
                    std::shared_ptr<Identifier> _id,
                    std::shared_ptr<Identifier> _base,
                    std::shared_ptr<VariableDeclarationStatementList> _localVars,
                    std::shared_ptr<MethodDeclarationList> _methods,
                    const Location& _loc)
                    : IClassDecl(_loc, std::move(_id)), base(std::move(_base)),
                      localVars(std::move(_localVars)), methods(std::move(_methods)) {}

            ClassDeclaration(
                    const std::shared_ptr<Identifier>& _id,
                    const std::shared_ptr<VariableDeclarationStatementList>& _localVars,
                    const std::shared_ptr<MethodDeclarationList>& _methods,
                    const Location& _loc)
                    : ClassDeclaration(_id, nullptr, _localVars, _methods, _loc) {}
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ClassDeclarationList : INodeList {
            explicit ClassDeclarationList(const Location& _loc)
                    : INodeList(_loc) {}
            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };


        struct MainClass : IClassDecl {
            std::shared_ptr<Identifier> argsName;
            std::shared_ptr<IStatement> st;
        public:
            MainClass(std::shared_ptr<Identifier> _id, std::shared_ptr<Identifier> _argsName, std::shared_ptr<IStatement> _st, const Location& _loc)
                    : IClassDecl(_loc, _id), argsName(std::move(_argsName)), st(std::move(_st)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };


        struct Program : INode {
            std::shared_ptr<MainClass> mainClass;
            std::shared_ptr<ClassDeclarationList> classDeclarationList;

            Program() = default;
            Program(std::shared_ptr<MainClass> _mainClass, std::shared_ptr<ClassDeclarationList> _cdl, const Location& _loc)
                    : INode(_loc), mainClass(std::move(_mainClass)), classDeclarationList(std::move(_cdl)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct NestedStatement : public IStatement {
            std::shared_ptr<CStatementList> statementList;

            explicit NestedStatement(std::shared_ptr<CStatementList> _statementList, const Location& _loc)
                    : IStatement(_loc), statementList(std::move(_statementList)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct IfStatement : IStatement {
            std::shared_ptr<IExpression> condition;
            std::shared_ptr<IStatement> ifStatement;
            std::shared_ptr<IStatement> elseStatement;

            IfStatement(std::shared_ptr<IExpression> _condition, std::shared_ptr<IStatement> _ifStatement,
                        std::shared_ptr<IStatement> _elseStatement, const Location& _loc)
                    : IStatement(_loc), condition(_condition), ifStatement(_ifStatement), elseStatement(_elseStatement) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct WhileStatement : IStatement {
            std::shared_ptr<IExpression> condition;
            std::shared_ptr<IStatement> statement;

            WhileStatement(std::shared_ptr<IExpression> _condition, std::shared_ptr<IStatement> _statement,
                    const Location& loc)
                    : IStatement(loc), condition(std::move(_condition)), statement(std::move(_statement)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct PrintStatement : IStatement {
            std::shared_ptr<IExpression> exp;

            explicit PrintStatement(std::shared_ptr<IExpression> _exp, const Location& _loc)
                    : IStatement(_loc), exp(_exp) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct AssignStatement : IStatement {
            std::shared_ptr<Identifier> id;
            std::shared_ptr<IExpression> exp;
        public:
            AssignStatement(std::shared_ptr<Identifier> _id, std::shared_ptr<IExpression> _exp, const Location& _loc)
                    : IStatement(_loc), id(_id), exp(_exp) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ArrayAssignStatement : IStatement {
            std::shared_ptr<Identifier> id;
            std::shared_ptr<IExpression> arrExp;
            std::shared_ptr<IExpression> exp;

            ArrayAssignStatement(
                    std::shared_ptr<Identifier> _id,
                    std::shared_ptr<IExpression> _arrExp,
                    std::shared_ptr<IExpression> _exp,
                    const Location& _loc)
                    : IStatement(_loc), id(std::move(_id)), arrExp(std::move(_arrExp)), exp(std::move(_exp)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
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
            std::shared_ptr<IExpression> left;
            std::shared_ptr<IExpression> right;
            BinOpType type;

            BinopExpression(
                    std::shared_ptr<IExpression> _left,
                    std::shared_ptr<IExpression> _right,
                    const BinOpType& _type,
                    const Location& _loc)
                    : IExpression(_loc), left(std::move(_left)), right(std::move(_right)), type(_type) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT

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
            std::shared_ptr<IExpression> arr;
            std::shared_ptr<IExpression> ind;

            ArrayItemExpression(std::shared_ptr<IExpression> _arr, std::shared_ptr<IExpression> _ind, const Location& _loc)
                    : IExpression(_loc), arr(std::move(_arr)), ind(std::move(_ind)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ArrayLengthExpression : IExpression {
            std::shared_ptr<IExpression> arr;

            explicit ArrayLengthExpression(std::shared_ptr<IExpression> _arr, const Location& _loc)
                    : IExpression(_loc), arr(
                    std::move(_arr)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct CallExpression : IExpression {
            std::shared_ptr<IExpression> obj;
            std::shared_ptr<Identifier> method;
            std::shared_ptr<ArgumentsList> args;

            CallExpression(std::shared_ptr<IExpression> _obj, std::shared_ptr<Identifier> _method, std::shared_ptr<ArgumentsList> _args, const Location& _loc)
                    : IExpression(_loc), obj(_obj), method(_method), args(_args) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct ConstExpression : IExpression {
            int value;

            explicit ConstExpression(int value, const Location& loc)
                    : IExpression(loc), value(value) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct BoolExpression : IExpression {
            bool value;

            explicit BoolExpression(bool value, const Location& loc)
                    : IExpression(loc), value(value) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct IdExpression : IExpression {
            std::shared_ptr<Identifier> id;
            bool isThis = false;

//            explicit IdExpression(const std::string& s, const Location& loc) : IExpression(loc), isThis(true) {}
            explicit IdExpression(std::shared_ptr<Identifier> _id, const Location& _loc)
            : IExpression(_loc), id(_id) {
                if (id->name == "this") {
                    isThis = true;
                }
            }

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct NewArrayExpression : IExpression {
//            Type* type;
            std::shared_ptr<IExpression> size;

            NewArrayExpression(std::shared_ptr<IExpression> _size, const Location& _loc)
                    : IExpression(_loc), size(std::move(_size)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct NewObjectExpression : IExpression {
            std::shared_ptr<Identifier> id;

            explicit NewObjectExpression(std::shared_ptr<Identifier> _id, const Location& _loc)
                    : IExpression(_loc), id(std::move(_id)) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

        struct NotExpression : IExpression {
            std::shared_ptr<IExpression> exp;
        public:
            explicit NotExpression(std::shared_ptr<IExpression> _exp, const Location& _loc)
                    : IExpression(_loc), exp(_exp) {}

            DEFINE_PRINT_ACCEPT
            DEFINE_IRTRANSLATE_ACCEPT
        };

#undef DEFINE_PRINT_ACCEPT
#undef DEFINE_IRTRANSLATE_ACCEPT
    }
}
