//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"
#include "nodes/Nodes.h"

#include <iostream>
#include <sstream>

namespace ast {
    void PrintVisitor::visit(const nodes::Identifier* id) const {
        fout << "id " << id->name << " (" << id << ");" << std::endl;
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
        fout << "Class [" << node <<"] -> ";
        node->id.accept(this);
        fout << "Class [" << node <<"] -> ";
        node->base.accept(this);
        fout << "Class [" << node <<"] -> ";
        node->localVars->accept(this);
        fout << "Class [" << node <<"] -> ";
        node->methods->accept(this);
    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {
        for (auto&& c : node->nodes) {
            fout << "Class list [" << node <<" -> ";
            c->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {
        for (auto&& var : node->nodes) {
            fout << "Vars list [" << node <<" -> ";
            var->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {
        fout << "var statement [" << node << "] -> ";
        node->var->accept(this);
    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {
        fout << "var [" << node << "] -> ";
        node->type->accept(this);
        fout << "var [" << node << "] -> ";
        node->id.accept(this);
    }

    void PrintVisitor::visit(const nodes::Type* node) const {
        switch (node->tt) {
            case nodes::TT_Array:
                fout << "int[] [" << node << "];" << std ::endl;
                break;
            case nodes::TT_Bool:
                fout << "bool [" << node << "];" << std ::endl;
                break;
            case nodes::TT_Int:
                fout << "int [" << node << "];" << std ::endl;
                break;
            case nodes::TT_Object:
                fout << "class [" << node << "] -> ";
                node->id.accept(this);
                break;
            case nodes::TT_Void:
                fout << "void [" << node << "];" << std ::endl;
                break;
            default:
                fout << "?? [" << node << "];" << std ::endl;

        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclarationList* node) const {
        for (auto&& method : node->nodes) {
            fout << "Methods [" << node << "] -> ";
            method->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {
        fout << "Method(){} [" << node << "] -> ";
        node->returnType->accept(this);
        fout << "Method(){} [" << node << "] -> ";
        node->id.accept(this);
        fout << "Method(){} [" << node << "] -> ";
        node->args->accept(this);
        fout << "Method(){} [" << node << "] -> ";
        node->statementList->accept(this);
        fout << "Method(){} [" << node << "] -> ";
        node->returnExp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {
        for (auto&& args : node->nodes) {
            fout << "Argument declarations [" << node << "] -> ";
            args->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::CStatementList* node) const {
        for (auto&& st : node->nodes) {
            fout << "Statements [" << node << "] -> ";
            st->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {
        fout << "Nested Statement [" << node << "] -> ";
        node->statementList->accept(this);
    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {
        fout << "If [" << node << "] -> ";
        node->condition->accept(this);
        fout << "If [" << node << "] -> ";
        node->ifStatement->accept(this);
        fout << "If [" << node << "] -> ";
        node->elseStatement->accept(this);
    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {
        fout << "While [" << node << "] -> ";
        node->condition->accept(this);
        fout << "While [" << node << "] -> ";
        node->statement->accept(this);
    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {
        fout << "Print [" << node <<"] -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {
        fout << "Assign [" << node <<"] -> ";
        node->id.accept(this);
        fout << "Assign [" << node <<"] -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {
        fout << "Arr[exp1] = exp2 [" << node << "] -> ";
        node->id.accept(this);
        fout << "Arr[exp1] = exp2 [" << node << "] -> ";
        node->arrExp->accept(this);
        fout << "Arr[exp1] = exp2 [" << node << "] -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {
        for (auto&& n : node->nodes) {
            fout << "Arguments [" << node << "] -> ";
            n->accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {
        fout << "Binary operation [" << node << "] -> ";
        node->left->accept(this);
        fout << "Binary operation [" << node << "] -> ";
        switch (node->type) {
            case nodes::BOT_Plus:
                fout << "+ [" << node <<"];" << std::endl;
                break;
            case nodes::BOT_Minus:
                fout << "- [" << node <<"];" << std::endl;
                break;
            case nodes::BOT_Multiply:
                fout << "* [" << node <<"];" << std::endl;
                break;
            case nodes::BOT_Less:
                fout << "< [" << node <<"];" << std::endl;
                break;
            case nodes::BOT_Equal:
                fout << "== [" << node <<"];" << std::endl;
                break;
            case nodes::BOT_And:
                fout << "&& [" << node <<"];" << std::endl;
                break;
            default:
                fout << "? [" << node <<"];" << std::endl;
        }
        fout << "Binary operation [" << node << "] -> ";
        node->right->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {
        fout << "GetItem [" << node <<"] -> ";
        node->arr->accept(this);
        fout << "GetItem [" << node <<"] -> ";
        node->ind->accept(this);
    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {
        fout << "Length [" << node <<"] -> ";
        node->arr->accept(this);
    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {
        fout << "Call [" << node << "] -> ";
        node->obj->accept(this);
        fout << "Call [" << node << "] -> ";
        node->method.accept(this);
        fout << "Call [" << node << "] -> ";
        node->args->accept(this);
    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {
        fout << "constant " << node->value << " [" << node << "];" << std::endl;
    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {
        if (node->value) {
            fout << "true [" << node <<"];" << std::endl;
        }
        else {
            fout << "false [" << node <<"];" << std::endl;
        }
    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {
        fout << "IdExpression [" << node << "] -> ";
        if (node->isThis) {
            fout << "this [" << node << "];" << std::endl;
        }
        else {
            node->id.accept(this);
        }
    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {
        fout << "New Array [" << node << "] -> ";
        node->type->accept(this);
        fout << "New Array [" << node << "] -> ";
        node->exp->accept(this);
    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {
        fout << "New Object [" << node << "] -> ";
        node->id.accept(this);
    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {
        fout << "Not [" << node << "] -> ";
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