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
            GET_NICE_ADDRESS
            auto nodeId = "NAME_" + s;
            fout << nodeId << ";" << std::endl;
            SET_NODE_LABEL("NAME " + node->label.name)
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
            GET_NICE_ADDRESS
            auto nodeId = "CALL_" + s;
            if (node->args != nullptr) {
                fout << nodeId << " -> ";
                node->args->accept(this);
            }
            else {
                fout << nodeId << ";" << std::endl;
            }
            SET_NODE_LABEL("CALL: " + node->func.name + "()")
        }

        void PrintVisitor::visit(const EseqExpression* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "ESEQ_" + s;
            if (node->stm == nullptr && node->exp == nullptr) {
                fout << nodeId << ";" << std::endl;
            }
            if (node->stm != nullptr) {
                fout << nodeId << " -> ";
                node->stm->accept(this);
            }
            if (node->exp != nullptr) {
                fout << nodeId << " -> ";
                node->exp->accept(this);
            }
            SET_NODE_LABEL("ESEQ")
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
            GET_NICE_ADDRESS
            auto nodeId = "EXP_" + s;
            if (node->exp != nullptr) {
                fout << nodeId << " -> ";
                node->exp->accept(this);
            }
            else {
                fout << nodeId << ";"  << std::endl;
            }
            SET_NODE_LABEL("EXP")
        }

        void PrintVisitor::visit(const JumpStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "JUMP_" + s;
            fout << nodeId << ";"  << std::endl;
            SET_NODE_LABEL("JUMP " + node->target.name)
        }

        void PrintVisitor::visit(const CondJumpStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "CJUMP_" + s;
            if (node->left == nullptr && node->right == nullptr) {
                fout << nodeId << ";"  << std::endl;
            }
            if (node->left != nullptr) {
                fout << nodeId << " -> ";
                node->left->accept(this);
            }
            if (node->right != nullptr) {
                fout << nodeId << " -> ";
                node->right->accept(this);
            }
            fout << nodeId << " -> ";
            LabelStatement(node->ifTarget).accept(this);

            fout << nodeId << " -> ";
            LabelStatement(node->elseTarget).accept(this);
            
            switch (node->op) {
                case RO_Eq:
                    SET_NODE_LABEL("CJUMP ==")
                    break;
                case RO_Ne:
                    SET_NODE_LABEL("CJUMP !=")
                    break;
                case RO_Lt:
                    SET_NODE_LABEL("CJUMP <")
                    break;
                case RO_Gt:
                    SET_NODE_LABEL("CJUMP >")
                    break;
                case RO_Le:
                    SET_NODE_LABEL("CJUMP <=")
                    break;
                case RO_Ge:
                    SET_NODE_LABEL("CJUMP >=")
                    break;
                case RO_Ult:
                case RO_Ugt:
                case RO_Ule:
                case RO_Uge:
                    SET_NODE_LABEL("CJUMP")
            }
        }

        void PrintVisitor::visit(const SeqStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "SEQ_" + s;
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
            SET_NODE_LABEL("SEQ")
        }

        void PrintVisitor::visit(const LabelStatement* node) const {
            GET_NICE_ADDRESS
            auto nodeId = "LABEL_" + s;
            fout << nodeId << ";" << std::endl;
            SET_NODE_LABEL("LABEL " + node->label.name);
        }
    }
}
