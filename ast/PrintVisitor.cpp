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

    void PrintVisitor::visit(const nodes::Identifier* id) const {
        std::stringstream s;
        s << id;
        s.ignore(2);
        fout << "id_" << id->name << "_" << s.rdbuf() << "_;" << std::endl;
    }

    void PrintVisitor::visit(const nodes::Program* program) const {
        fout << "program -> ";
        program->mainClass->accept(this);
        fout << "program -> ";
        program->classDeclarationList->accept(this);
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
        GET_NICE_ADDRESS
        fout << "Class_" << s << "_ -> ";
        node->id.accept(this);
        fout << "Class_" << s << "_ -> ";
        node->base.accept(this);
        fout << "Class_" << s << "_ -> ";
        node->localVars->accept(this);
        fout << "Class_" << s << "_ -> ";
        node->methods->accept(this);
    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {
        GET_NICE_ADDRESS
        for (auto&& c : node->nodes) {
            fout << "Class_list_" << s << " -> ";
            c->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {
        GET_NICE_ADDRESS
        for (auto&& var : node->nodes) {
            fout << "Vars_list_" << s << " -> ";
            var->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {
        GET_NICE_ADDRESS
        fout << "var_statement_" << s << "_ -> ";
        node->var->accept(this);
    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {
        GET_NICE_ADDRESS
        fout << "var_" << s << "_ -> ";
        node->type->accept(this);
        fout << "var_" << s << "_ -> ";
        node->id.accept(this);
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
            fout << "Methods_" << s << "_ -> ";
            method->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {
        GET_NICE_ADDRESS
        fout << "Method_" << s << "_ -> ";
        node->returnType->accept(this);
        fout << "Method_" << s << "_ -> ";
        node->id.accept(this);
        fout << "Method_" << s << "_ -> ";
        node->args->accept(this);
        fout << "Method_" << s << "_ -> ";
        node->statementList->accept(this);
        fout << "Method_" << s << "_ -> ";
        node->returnExp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {
        GET_NICE_ADDRESS
        for (auto&& args : node->nodes) {
            fout << "Argument_declarations_" << s << "_ -> ";
            args->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::CStatementList* node) const {
        GET_NICE_ADDRESS
        for (auto&& st : node->nodes) {
            fout << "Statements_" << s << "_ -> ";
            st->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {
        GET_NICE_ADDRESS
        fout << "Nested Statement_" << s << "_ -> ";
        node->statementList->accept(this);
    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {
        GET_NICE_ADDRESS
        fout << "If_" << s << "_ -> ";
        node->condition->accept(this);
        fout << "If_" << s << "_ -> ";
        node->ifStatement->accept(this);
        fout << "If_" << s << "_ -> ";
        node->elseStatement->accept(this);
    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {
        GET_NICE_ADDRESS
        fout << "While_" << s << "_ -> ";
        node->condition->accept(this);
        fout << "While_" << s << "_ -> ";
        node->statement->accept(this);
    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {
        GET_NICE_ADDRESS
        fout << "Print_" << s << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {
        GET_NICE_ADDRESS
        fout << "Assign_" << s << "_ -> ";
        node->id.accept(this);
        fout << "Assign_" << s << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {
        GET_NICE_ADDRESS
        fout << "Arr[exp1] = exp2_" << s << "_ -> ";
        node->id.accept(this);
        fout << "Arr[exp1] = exp2_" << s << "_ -> ";
        node->arrExp->accept(this);
        fout << "Arr[exp1] = exp2_" << s << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {
        GET_NICE_ADDRESS
        for (auto&& n : node->nodes) {
            fout << "Arguments_" << s << "_ -> ";
            n->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {
        GET_NICE_ADDRESS
        fout << "Binary_operation_" << s << "_ -> ";
        node->left->accept(this);
        fout << "Binary_operation_" << s << "_ -> ";
        switch (node->type) {
            case nodes::BOT_Plus:
                fout << "plus_" << s << "_;" << std::endl;
                break;
            case nodes::BOT_Minus:
                fout << "minus_" << s << "_;" << std::endl;
                break;
            case nodes::BOT_Multiply:
                fout << "mult_" << s << "_;" << std::endl;
                break;
            case nodes::BOT_Less:
                fout << "less_" << s << "_;" << std::endl;
                break;
            case nodes::BOT_Equal:
                fout << "equal_" << s << "_;" << std::endl;
                break;
            case nodes::BOT_And:
                fout << "and_" << s << "_;" << std::endl;
                break;
            default:
                fout << "xxx_" << s << "_;" << std::endl;
        }
        fout << "Binary_operation_" << s << "_ -> ";
        node->right->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {
        GET_NICE_ADDRESS
        fout << "GetItem_" << s << "_ -> ";
        node->arr->accept(this);
        fout << "GetItem_" << s << "_ -> ";
        node->ind->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {
        GET_NICE_ADDRESS
        fout << "Length_" << s << "_ -> ";
        node->arr->accept(this);
    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {
        GET_NICE_ADDRESS
        fout << "Call_" << s << "_ -> ";
        node->obj->accept(this);
        fout << "Call_" << s << "_ -> ";
        node->method.accept(this);
        fout << "Call_" << s << "_ -> ";
        node->args->accept(this);
    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {
        GET_NICE_ADDRESS
        fout << "constant_" << node->value << "_" << s << "_;" << std::endl;
    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {
        GET_NICE_ADDRESS
        if (node->value) {
            fout << "true_" << s << "_;" << std::endl;
        } else {
            fout << "false_" << s << "_;" << std::endl;
        }
    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {
        GET_NICE_ADDRESS
        fout << "IdExpression_" << s << "_ -> ";
        if (node->isThis) {
            fout << "this_" << s << "_;" << std::endl;
        } else {
            node->id.accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {
        GET_NICE_ADDRESS
        fout << "New_Array_" << s << "_ -> ";
        node->type->accept(this);
        fout << "New_Array_" << s << "_ -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {
        GET_NICE_ADDRESS
        fout << "New_Object_" << s << "_ -> ";
        node->id.accept(this);
    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {
        GET_NICE_ADDRESS
        fout << "Not_" << s << "_ -> ";
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