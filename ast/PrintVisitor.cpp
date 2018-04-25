//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"
#include "nodes/Nodes.h"

#include <iostream>
#include <sstream>

namespace ast {

#define GET_NICE_ADDRESS \
    std::stringstream ss;\
    ss << node;\
    ss.ignore(2);\
    std::string s = ss.str();

#define SET_NODE_LABEL(label) \
    fout << nodeId << "[label=\"" << label << "\"];" << std::endl;

    void PrintVisitor::visit(const nodes::Identifier* id) const {
        std::stringstream s;
        s << id;
        s.ignore(2);
        std::string nodeId = "id_" + id->name + "_" + s.str();
        fout << nodeId << ";" << std::endl;
        SET_NODE_LABEL("Id " + id->name)
    }

    void PrintVisitor::visit(const nodes::Program* program) const {
        fout << "program -> ";
        program->mainClass->accept(this);
        fout << "program -> ";
        program->classDeclarationList->accept(this);
    }

    void PrintVisitor::visit(const nodes::MainClass* node) const {
        fout << "mainClass -> ";
        node->name.accept(this);
        fout << "mainClass -> ";
        node->argsName.accept(this);
        fout << "mainClass -> ";
        node->st->accept(this);
    }

    void PrintVisitor::visit(const nodes::ClassDeclaration* node) const {
        GET_NICE_ADDRESS
        auto nodeId =  "Class_" + s;
        fout << nodeId << " -> ";
        node->id.accept(this);
        fout << nodeId << " -> ";
        node->base.accept(this);
        fout << nodeId << " -> ";
        node->localVars->accept(this);
        fout << nodeId << " -> ";
        node->methods->accept(this);
        SET_NODE_LABEL("Class " + node->id.name)
    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {
        GET_NICE_ADDRESS
        for (auto&& c : node->nodes) {
            auto nodeId = "Class_list_" + s;
            fout << nodeId << " -> ";
            c->accept(this);
            SET_NODE_LABEL("Classes")
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {
        GET_NICE_ADDRESS
        for (auto&& var : node->nodes) {
            auto nodeId = "Vars_list_" + s;
            fout << nodeId << " -> ";
            var->accept(this);
            SET_NODE_LABEL("Variables")
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "var_statement_" + s;
        fout << nodeId << " -> ";
        node->var->accept(this);
        SET_NODE_LABEL("Var decl")
    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "var_" + s;
//        fout << nodeId << " -> ";
//        node->type->accept(this);
        fout << nodeId << " -> ";
        node->id.accept(this);
        SET_NODE_LABEL(node->id.name + " : " + node->type->getTT())
    }

    void PrintVisitor::visit(const nodes::Type* node) const {
        GET_NICE_ADDRESS
        switch (node->tt) {
            case nodes::TT_Array:
                fout << "intArr_" << s << "_;" << std::endl;
                break;
            case nodes::TT_Bool:
                fout << "bool_" << s << "_;" << std::endl;
                break;
            case nodes::TT_Int:
                fout << "int_" << s << "_;" << std::endl;
                break;
            case nodes::TT_Object:
                fout << "class_" << s << "_ -> ";
                node->id.accept(this);
                break;
            case nodes::TT_Void:
                fout << "void_" << s << "_;" << std::endl;
                break;
            default:
                fout << "??_" << s << "_;" << std::endl;

        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclarationList* node) const {
        GET_NICE_ADDRESS
        for (auto&& method : node->nodes) {
            auto nodeId = "Methods_" + s;
            fout << nodeId << " -> ";
            method->accept(this);
            SET_NODE_LABEL("Methods")
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Method_" + s;
        fout << nodeId << " -> ";
        node->returnType->accept(this);
        fout << nodeId << " -> ";
        node->id.accept(this);
        fout << nodeId << " -> ";
        node->args->accept(this);
        fout << nodeId << " -> ";
        node->statementList->accept(this);
        fout << nodeId << " -> ";
        node->returnExp->accept(this);
        SET_NODE_LABEL("Method " + node->id.name)
    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {
        GET_NICE_ADDRESS
        for (auto&& args : node->nodes) {
            auto nodeId = "Argument_declarations_" + s;
            fout << nodeId << " -> ";
            args->accept(this);
            SET_NODE_LABEL("Arg declaration")
        }
    }

    void PrintVisitor::visit(const nodes::CStatementList* node) const {
        GET_NICE_ADDRESS
        for (auto&& st : node->nodes) {
            auto nodeId = "Statements_" + s;
            fout << nodeId << " -> ";
            st->accept(this);
            SET_NODE_LABEL("Statements")
        }
    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Nested Statement_" + s;
        fout << nodeId << " -> ";
        node->statementList->accept(this);
        SET_NODE_LABEL("Nested Stm")
    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "If_" + s;
        fout << nodeId << " -> ";
        node->condition->accept(this);
        fout << nodeId << " -> ";
        node->ifStatement->accept(this);
        fout << nodeId << " -> ";
        node->elseStatement->accept(this);
        SET_NODE_LABEL("If-else")
    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "While_" + s;
        fout << nodeId << " -> ";
        node->condition->accept(this);
        fout << nodeId << " -> ";
        node->statement->accept(this);
        SET_NODE_LABEL("While")
    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Print_" + s;
        fout << nodeId << " -> ";
        node->exp->accept(this);
        SET_NODE_LABEL("Print")
    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Assign_" + s;
        fout << nodeId << " -> ";
        node->id.accept(this);
        fout << nodeId << " -> ";
        node->exp->accept(this);
        SET_NODE_LABEL("=")
    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "ArrayAssign_" + s;
        fout << nodeId << " -> ";
        node->id.accept(this);
        fout << nodeId << " -> ";
        node->arrExp->accept(this);
        fout << nodeId << " -> ";
        node->exp->accept(this);
        SET_NODE_LABEL("arr[i] = exp")
    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {
        GET_NICE_ADDRESS
        for (auto&& n : node->nodes) {
            auto nodeId = "Arguments_" + s;
            fout << nodeId << " -> ";
            n->accept(this);
            SET_NODE_LABEL("Args")
        }
    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = node->binOpTypeToStr() + "_" + s;
        fout << nodeId << " -> ";
        node->left->accept(this);
        fout << nodeId << " -> ";
        node->right->accept(this);

        switch (node->type) {
            case nodes::BOT_Plus:
                SET_NODE_LABEL("+")
                break;
            case nodes::BOT_Minus:
                SET_NODE_LABEL("-")
                break;
            case nodes::BOT_Multiply:
                SET_NODE_LABEL("*")
                break;
            case nodes::BOT_Less:
                SET_NODE_LABEL("<")
                break;
            case nodes::BOT_Equal:
                SET_NODE_LABEL("==")
                break;
            case nodes::BOT_And:
                SET_NODE_LABEL("&&")
                break;
            default:
                SET_NODE_LABEL("")
        }
    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "GetItem_" + s;
        fout << nodeId << " -> ";
        node->arr->accept(this);
        fout << nodeId << " -> ";
        node->ind->accept(this);
        SET_NODE_LABEL("[]")
    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Length_" + s;
        fout << nodeId << " -> ";
        node->arr->accept(this);
        SET_NODE_LABEL(".Length")
    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Call_" + s;
        fout << nodeId << " -> ";
        node->obj->accept(this);
        fout << nodeId << " -> ";
        node->method.accept(this);
        fout << nodeId << " -> ";
        node->args->accept(this);
        SET_NODE_LABEL(node->method.name + "()")
    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "constant_" + s;
        fout << nodeId << std::endl;
        std::stringstream itostr;
        itostr << node->value;
        SET_NODE_LABEL(itostr.rdbuf())
    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Bool_" + s;
        fout << nodeId << ";" << std::endl;
        SET_NODE_LABEL((node->value ? "true" : "false"))
    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "IdExp_" + s;
        fout << nodeId;
        if (node->isThis) {
            fout << ";" << std::endl;
            SET_NODE_LABEL("this")
        } else {
            fout << " -> ";
            node->id.accept(this);
            SET_NODE_LABEL("Id Exp")
        }
    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "New_Array_" + s;
//        fout << nodeId << " -> ";
//        node->type->accept(this);
        fout << nodeId << " -> ";
        node->exp->accept(this);
        SET_NODE_LABEL("new type[]")
    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "New_Object_" + s;
        fout << nodeId << " -> ";
        node->id.accept(this);
        SET_NODE_LABEL("new Obj")
    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {
        GET_NICE_ADDRESS
        auto nodeId = "Not_" + s;
        fout << nodeId << " -> ";
        node->exp->accept(this);
        SET_NODE_LABEL("Not")
    }

    PrintVisitor::PrintVisitor(const std::string& filename) {
        fout.open(filename);
        fout << "digraph G {" << std::endl;
    }


    void PrintVisitor::finish() {
        fout << "}" << std::endl;
        fout.close();
    }


}