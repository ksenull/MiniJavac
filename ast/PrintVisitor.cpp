//
// Created by ksenull on 3/4/18.
//
#include "PrintVisitor.h"
#include "nodes/Nodes.h"

#include <iostream>
#include <sstream>

namespace ast {

    std::string declareNodeId(const nodes::INode* node, const std::string& idStr) {
        std::stringstream ss;
        
        ss << node;
        ss.ignore(2);
        std::string addr;
        ss >> addr;

        auto&& nodeId = idStr + "_" + addr;

        return nodeId;
    }

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

        if (!program->classDeclarationList->nodes.empty()) {
            fout << "program -> ";
            program->classDeclarationList->accept(this);
        }
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
        auto&& nodeId = declareNodeId(node, "class");

        fout << nodeId << " -> ";
        node->id.accept(this);

        if (!node->base.name.empty()) {
            fout << nodeId << " -> ";
            node->base.accept(this);
        }
        if (!node->localVars->nodes.empty()) {
            fout << nodeId << " -> ";
            node->localVars->accept(this);
        }
        if (!node->methods->nodes.empty()) {
            fout << nodeId << " -> ";
            node->methods->accept(this);
        }
        SET_NODE_LABEL("Class " + node->id.name)
    }

    void PrintVisitor::visit(const nodes::ClassDeclarationList* node) const {
        auto&& nodeId = declareNodeId(node, "classes");
        for (auto&& c : node->nodes) {

            fout << nodeId << " -> ";
            c->accept(this);

            SET_NODE_LABEL("Classes");
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatementList* node) const {
        auto&& nodeId = declareNodeId(node, "vars");
        for (auto&& var : node->nodes) {

            fout << nodeId << " -> ";
            var->accept(this);

            SET_NODE_LABEL("Variables");
        }
    }

    void PrintVisitor::visit(const nodes::VariableDeclarationStatement* node) const {
        auto&& nodeId = declareNodeId(node, "var_stm");

        fout << nodeId << " -> ";
        node->var->accept(this);

        SET_NODE_LABEL("Var decl");
    }

    void PrintVisitor::visit(const nodes::VariableDeclaration* node) const {
        auto&& nodeId = declareNodeId(node, "var");

        fout << nodeId << " -> ";
        node->id.accept(this);

        SET_NODE_LABEL(node->id.name + " : " + node->type->getTT())
    }

    void PrintVisitor::visit(const nodes::Type* node) const {
        switch (node->tt) {
            case nodes::TT_Array: {
                auto&& nodeId = declareNodeId(node, "int_arr");
                fout << nodeId << ";" << std::endl;
                SET_NODE_LABEL("int[]");
                break;
            }
            case nodes::TT_Bool: {
                auto&& nodeId = declareNodeId(node, "bool");
                fout << nodeId << ";" << std::endl;
                SET_NODE_LABEL("boolean");
                break;
            }
            case nodes::TT_Int: {
                auto&& nodeId = declareNodeId(node, "int");
                fout << nodeId << ";" << std::endl;

                SET_NODE_LABEL("int");
                break;
            }
            case nodes::TT_Object: {
                auto&& nodeId = declareNodeId(node, "user_type");
                fout << nodeId << " -> ";
                node->id.accept(this);
                SET_NODE_LABEL("User type");
                break;
            }
            case nodes::TT_Void: {
                auto&& nodeId = declareNodeId(node, "void_");
                fout << nodeId << ";" << std::endl;
                SET_NODE_LABEL("void");
                break;
            }
            default:
                break;
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclarationList* node) const {
        auto&& nodeId = declareNodeId(node, "methods_");

        for (auto&& method : node->nodes) {
            fout << nodeId << " -> ";
            method->accept(this);

            SET_NODE_LABEL("Methods");
        }
    }

    void PrintVisitor::visit(const nodes::MethodDeclaration* node) const {
        auto&& nodeId = declareNodeId(node, "method");

        fout << nodeId << " -> ";
        node->returnType->accept(this);

        fout << nodeId << " -> ";
        node->id.accept(this);

        if (!node->args->nodes.empty()) {
            fout << nodeId << " -> ";
            node->args->accept(this);
        }
        if (!node->statementList->nodes.empty()) {
            fout << nodeId << " -> ";
            node->statementList->accept(this);
        }
        if (node->returnExp) {
            fout << nodeId << " -> ";
            node->returnExp->accept(this);
        }
        SET_NODE_LABEL("Method " + node->id.name)
    }

    void PrintVisitor::visit(const nodes::ArgumentDeclarationList* node) const {
        auto&& nodeId = declareNodeId(node, "args_decls");
        for (auto&& args : node->nodes) {
            fout << nodeId << " -> ";
            args->accept(this);
            SET_NODE_LABEL("Arg");
        }
    }

    void PrintVisitor::visit(const nodes::CStatementList* node) const {
        auto&& nodeId = declareNodeId(node, "stms");

        for (auto&& st : node->nodes) {
            fout << nodeId << " -> ";
            st->accept(this);

            SET_NODE_LABEL("Statements");
        }
    }

    void PrintVisitor::visit(const nodes::NestedStatement* node) const {
        auto&& nodeId = declareNodeId(node, "nested_stm");

        if (!node->statementList->nodes.empty()) {
            fout << nodeId << " -> ";
            node->statementList->accept(this);
        }
        SET_NODE_LABEL("Nested Stm");
    }

    void PrintVisitor::visit(const nodes::IfStatement* node) const {
        auto&& nodeId = declareNodeId(node, "if");

        fout << nodeId << " -> ";
        node->condition->accept(this);

        fout << nodeId << " -> ";
        node->ifStatement->accept(this);

        fout << nodeId << " -> ";
        node->elseStatement->accept(this);

        SET_NODE_LABEL("If-else");
    }

    void PrintVisitor::visit(const nodes::WhileStatement* node) const {
        auto&& nodeId = declareNodeId(node, "while");

        fout << nodeId << " -> ";
        node->condition->accept(this);

        fout << nodeId << " -> ";
        node->statement->accept(this);

        SET_NODE_LABEL("While");
    }

    void PrintVisitor::visit(const nodes::PrintStatement* node) const {
        auto&& nodeId = declareNodeId(node, "print");

        fout << nodeId << " -> ";
        node->exp->accept(this);

        SET_NODE_LABEL("Print");
    }

    void PrintVisitor::visit(const nodes::AssignStatement* node) const {
        auto&& nodeId = declareNodeId(node, "assign_");

        fout << nodeId << " -> ";
        node->id.accept(this);

        fout << nodeId << " -> ";
        node->exp->accept(this);

        SET_NODE_LABEL("=");
    }

    void PrintVisitor::visit(const nodes::ArrayAssignStatement* node) const {
        auto&& nodeId = declareNodeId(node, "arr_assign");

        fout << nodeId << " -> ";
        node->id.accept(this);

        fout << nodeId << " -> ";
        node->arrExp->accept(this);

        fout << nodeId << " -> ";
        node->exp->accept(this);

        SET_NODE_LABEL("arr[i] = exp");
    }

    void PrintVisitor::visit(const nodes::ArgumentsList* node) const {
        auto&& nodeId = declareNodeId(node, "args");
        for (auto&& n : node->nodes) {

            fout << nodeId << " -> ";
            n->accept(this);

            SET_NODE_LABEL("Args");
        }
    }

    void PrintVisitor::visit(const nodes::BinopExpression* node) const {
        auto&& nodeId = declareNodeId(node, node->binOpTypeToStr());

        fout << nodeId << " -> ";
        node->left->accept(this);

        fout << nodeId << " -> ";
        node->right->accept(this);

        switch (node->type) {
            case nodes::BOT_Plus:
                SET_NODE_LABEL("+");
                break;
            case nodes::BOT_Minus:
                SET_NODE_LABEL("-");
                break;
            case nodes::BOT_Multiply:
                SET_NODE_LABEL("*");
                break;
            case nodes::BOT_Less:
                SET_NODE_LABEL("<");
                break;
            case nodes::BOT_Equal:
                SET_NODE_LABEL("==");
                break;
            case nodes::BOT_And:
                SET_NODE_LABEL("&&");
                break;
            default:
                SET_NODE_LABEL("");
        }
    }

    void PrintVisitor::visit(const nodes::ArrayItemExpression* node) const {
        auto&& nodeId = declareNodeId(node, "get_item");

        fout << nodeId << " -> ";
        node->arr->accept(this);

        fout << nodeId << " -> ";
        node->ind->accept(this);

        SET_NODE_LABEL("[]");
    }

    void PrintVisitor::visit(const nodes::ArrayLengthExpression* node) const {
        auto&& nodeId = declareNodeId(node, "length");

        fout << nodeId << " -> ";
        node->arr->accept(this);

        SET_NODE_LABEL(".Length");
    }

    void PrintVisitor::visit(const nodes::CallExpression* node) const {
        auto&& nodeId = declareNodeId(node, "call");

        fout << nodeId << " -> ";
        node->obj->accept(this);

        fout << nodeId << " -> ";
        node->method.accept(this);

        if (!node->args->nodes.empty()) {
            fout << nodeId << " -> ";
            node->args->accept(this);
        }

        SET_NODE_LABEL(node->method.name + "()");
    }

    void PrintVisitor::visit(const nodes::ConstExpression* node) const {
        auto&& nodeId = declareNodeId(node, "const");

        fout << nodeId << ";" << std::endl;

        std::stringstream itostr;
        itostr << node->value;
        SET_NODE_LABEL(itostr.rdbuf())
    }

    void PrintVisitor::visit(const nodes::BoolExpression* node) const {
        auto&& nodeId = declareNodeId(node, "bool_exp");

        fout << nodeId << ";" << std::endl;

        SET_NODE_LABEL((node->value ? "true" : "false"))
    }

    void PrintVisitor::visit(const nodes::IdExpression* node) const {
        auto&& nodeId = declareNodeId(node, "id_exp");

        fout << nodeId;
        if (node->isThis) {
            fout << ";" << std::endl;

            SET_NODE_LABEL("this");
        } else {
            fout << " -> ";
            node->id.accept(this);

            SET_NODE_LABEL("id");
        }
    }

    void PrintVisitor::visit(const nodes::NewArrayExpression* node) const {
        auto&& nodeId = declareNodeId(node, "new_arr");

        fout << nodeId << " -> ";
        node->exp->accept(this);

        SET_NODE_LABEL("new type[]");
    }

    void PrintVisitor::visit(const nodes::NewObjectExpression* node) const {
        auto&& nodeId = declareNodeId(node, "new_obj");

        fout << nodeId << " -> ";
        node->id.accept(this);

        SET_NODE_LABEL("new Obj");
    }

    void PrintVisitor::visit(const nodes::NotExpression* node) const {
        auto&& nodeId = declareNodeId(node, "not");

        fout << nodeId << " -> ";
        node->exp->accept(this);

        SET_NODE_LABEL("Not");
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