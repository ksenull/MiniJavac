//
// Created by ksenull on 5/2/18.
//
#include "PrintVisitor.h"
#include "Expressions.h"
#include "Statements.h"

namespace ir {
    namespace tree {
#define GET_NICE_ADDRESS \
    std::stringstream ss;\
    ss << node;\
    ss.ignore(2);\
    std::string s = ss.str();

#define SET_NODE_LABEL(label) \
    fout << nodeId << "[label=\"" << label << "\"];" << std::endl;


        PrintVisitor::PrintVisitor(const std::string& filename) {
            fout.open(filename);
            fout << "digraph G {" << std::endl;
        }

        void PrintVisitor::finish() {
            fout << "}" << std::endl;
            fout.close();
        }

        void PrintVisitor::visit(const CExpressionList* node) const {

        }

        void PrintVisitor::visit(const ConstExpression* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "CONST_" + s;
            fout << nodeId << ";" << std::endl;
            std::stringstream itoass;
            itoass << node->i;
            SET_NODE_LABEL(itoass.str())
        }

        void PrintVisitor::visit(const NameExpression* node) const {

        }

        void PrintVisitor::visit(const TempExpression* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "TEMP_" + s;
            fout << nodeId << ";" << std::endl;
            SET_NODE_LABEL("TEMP") //TODO num and values
        }

        void PrintVisitor::visit(const BinopExpression* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "BINOP_" + s;
            if (node->left == nullptr && node->right == nullptr) {
                fout << nodeId << ";" << std::endl;
            }
            if (node->left != nullptr) {
                fout << nodeId << " -> ";
                node->left->accept(this);
            }
            if (node->right != nullptr) {
                fout << nodeId << " -> ";
                node->right->accept(this);
            }
            switch (node->op) {
                case BO_Plus:
                    SET_NODE_LABEL("+")
                    break;
                case BO_Minus:
                    SET_NODE_LABEL("-")
                    break;
                case BO_Mul:
                    SET_NODE_LABEL("*")
                    break;
                case BO_Div:
                    SET_NODE_LABEL("%")
                    break;
                case BO_And:
                    SET_NODE_LABEL("&&")
                    break;
                case BO_Or:
                    SET_NODE_LABEL("||")
                    break;
                case BO_Lshift:
                    SET_NODE_LABEL("<<")
                    break;
                case BO_Rshift:
                    SET_NODE_LABEL(">>")
                    break;
                case BO_Arshift:
                case BO_Xor:
                    SET_NODE_LABEL("^")
                    break;
            }
        }

        void PrintVisitor::visit(const MemExpression* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "MEM_" + s;
            if (node->addr == nullptr) {
                fout << nodeId << ";" << std::endl;
            }
            else {
                fout << nodeId << " -> ";
                node->addr->accept(this);
            }
            SET_NODE_LABEL("MEM")
        }

        void PrintVisitor::visit(const CallExpression* node) const {

        }

        void PrintVisitor::visit(const EseqExpression* node) const {

        }

        void PrintVisitor::visit(const StatementList* node) const {

        }

        void PrintVisitor::visit(const MoveStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "MOVE_" + s;
            if (node->source == nullptr && node->target == nullptr) {
                fout << nodeId << ";" << std::endl;
            }
            if (node->target != nullptr) {
                fout << nodeId << " -> ";
                node->target->accept(this);
            }
            if (node->source != nullptr) {
                fout << nodeId << " -> ";
                node->source->accept(this);
            }
            SET_NODE_LABEL("MOVE")
        }

        void PrintVisitor::visit(const ExpStatement* node) const {

        }

        void PrintVisitor::visit(const JumpStatement* node) const {

        }

        void PrintVisitor::visit(const CondJumpStatement* node) const {

        }

        void PrintVisitor::visit(const SeqStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "SEQ_" + s;
            fout << nodeId << " -> ";
            node->left->accept(this);
            fout << nodeId << " -> ";
            node->right->accept(this);
            SET_NODE_LABEL("SEQ")
        }

        void PrintVisitor::visit(const LabelStatement* node) const {

        }
    }
}
