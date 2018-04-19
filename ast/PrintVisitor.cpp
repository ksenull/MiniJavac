//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"
#include "nodes/Nodes.h"

#include <iostream>
#include <sstream>

namespace ast {

#define GET_NICE_ADDRESS(s) {\
    s << node;\
    s.ignore(2);\
    }

    void PrintVisitor::visit(const nodes::Identifier* id) const {
        std::stringstream s;
        s << id;
        s.ignore(2);
        fout << "id_" << id->name << "_" << s.rdbuf() << "_;" << std::endl;
    }

    void PrintVisitor::visit(const nodes::Program* program) const {
        fout << "program -> ";
        program->mainClass->accept(this);
    }

    void PrintVisitor::visit(const nodes::MainClass* node) const {
        fout << "mainClass -> ";
        node->mainClass.accept(this);
        fout << "mainClass -> ";
        node->argsName.accept(this);
        fout << "mainClass -> ";
        node->st->accept(this);
    }

    void PrintVisitor::visit(const nodes::ClassDeclaration* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Class_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
        fout << "Class_" << s.rdbuf() << "_ -> ";
        node->base.accept(this);
        fout << "Class_" << s.rdbuf() << "_ -> ";
        node->localVars->accept(this);
        fout << "Class_" << s.rdbuf() << "_ -> ";
        node->methods->accept(this);
    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& c : node->nodes) {
            fout << "Class_list_" << s.rdbuf() << " -> ";
            c->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& var : node->nodes) {
            fout << "Vars_list_" << s.rdbuf() << " -> ";
            var->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "var_statement_" << s.rdbuf() << "_ -> ";
        node->var->accept(this);
    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "var_" << s.rdbuf() << "_ -> ";
        node->type->accept(this);
        fout << "var_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
    }

    void PrintVisitor::visit(const nodes::Type* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        switch (node->tt) {
            case nodes::TT_Array:
                fout << "intArr_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::TT_Bool:
                fout << "bool_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::TT_Int:
                fout << "int_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::TT_Object:
                fout << "class_" << s.rdbuf() << "_ -> ";
                node->id.accept(this);
                break;
            case nodes::TT_Void:
                fout << "void_" << s.rdbuf() << "_;" << std::endl;
                break;
            default:
                fout << "??_" << s.rdbuf() << "_;" << std::endl;

        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclarationList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& method : node->nodes) {
            fout << "Methods_" << s.rdbuf() << "_ -> ";
            method->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Method_" << s.rdbuf() << "_ -> ";
        node->returnType->accept(this);
        fout << "Method_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
        fout << "Method_" << s.rdbuf() << "_ -> ";
        node->args->accept(this);
        fout << "Method_" << s.rdbuf() << "_ -> ";
        node->statementList->accept(this);
        fout << "Method_" << s.rdbuf() << "_ -> ";
        node->returnExp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& args : node->nodes) {
            fout << "Argument_declarations_" << s.rdbuf() << "_ -> ";
            args->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::CStatementList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& st : node->nodes) {
            fout << "Statements_" << s.rdbuf() << "_ -> ";
            st->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Nested Statement_" << s.rdbuf() << "_ -> ";
        node->statementList->accept(this);
    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "If_" << s.rdbuf() << "_ -> ";
        node->condition->accept(this);
        fout << "If_" << s.rdbuf() << "_ -> ";
        node->ifStatement->accept(this);
        fout << "If_" << s.rdbuf() << "_ -> ";
        node->elseStatement->accept(this);
    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "While_" << s.rdbuf() << "_ -> ";
        node->condition->accept(this);
        fout << "While_" << s.rdbuf() << "_ -> ";
        node->statement->accept(this);
    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Print_" << s.rdbuf() << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Assign_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
        fout << "Assign_" << s.rdbuf() << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Arr[exp1] = exp2_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
        fout << "Arr[exp1] = exp2_" << s.rdbuf() << "_ -> ";
        node->arrExp->accept(this);
        fout << "Arr[exp1] = exp2_" << s.rdbuf() << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        for (auto&& n : node->nodes) {
            fout << "Arguments_" << s.rdbuf() << "_ -> ";
            n->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Binary_operation_" << s.rdbuf() << "_ -> ";
        node->left->accept(this);
        fout << "Binary_operation_" << s.rdbuf() << "_ -> ";
        switch (node->type) {
            case nodes::BOT_Plus:
                fout << "+_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::BOT_Minus:
                fout << "-_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::BOT_Multiply:
                fout << "*_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::BOT_Less:
                fout << "<_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::BOT_Equal:
                fout << "==_" << s.rdbuf() << "_;" << std::endl;
                break;
            case nodes::BOT_And:
                fout << "&&_" << s.rdbuf() << "_;" << std::endl;
                break;
            default:
                fout << "?_" << s.rdbuf() << "_;" << std::endl;
        }
        fout << "Binary_operation_" << s.rdbuf() << "_ -> ";
        node->right->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "GetItem_" << s.rdbuf() << "_ -> ";
        node->arr->accept(this);
        fout << "GetItem_" << s.rdbuf() << "_ -> ";
        node->ind->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Length_" << s.rdbuf() << "_ -> ";
        node->arr->accept(this);
    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Call_" << s.rdbuf() << "_ -> ";
        node->obj->accept(this);
        fout << "Call_" << s.rdbuf() << "_ -> ";
        node->method.accept(this);
        fout << "Call_" << s.rdbuf() << "_ -> ";
        node->args->accept(this);
    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "constant_" << node->value << "_" << s.rdbuf() << "_;" << std::endl;
    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        if (node->value) {
            fout << "true_" << s.rdbuf() << "_;" << std::endl;
        } else {
            fout << "false_" << s.rdbuf() << "_;" << std::endl;
        }
    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "IdExpression_" << s.rdbuf() << "_ -> ";
        if (node->isThis) {
            fout << "this_" << s.rdbuf() << "_;" << std::endl;
        } else {
            node->id.accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "New_Array_" << s.rdbuf() << "_ -> ";
        node->type->accept(this);
        fout << "New_Array_" << s.rdbuf() << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "New_Object_" << s.rdbuf() << "_ -> ";
        node->id.accept(this);
    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {
        std::stringstream s;
        GET_NICE_ADDRESS(s)
        fout << "Not_" << s.rdbuf() << "_ -> ";
        node->exp->accept(this);
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