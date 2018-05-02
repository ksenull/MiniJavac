//
// Created by ksenull on 5/2/18.
//
#include "PrintVisitor.h"

namespace ir {
    namespace tree {

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

        }

        void PrintVisitor::visit(const NameExpression* node) const {

        }

        void PrintVisitor::visit(const TempExpression* node) const {

        }

        void PrintVisitor::visit(const BinopExpression* node) const {

        }

        void PrintVisitor::visit(const MemExpression* node) const {

        }

        void PrintVisitor::visit(const CallExpression* node) const {

        }

        void PrintVisitor::visit(const EseqExpression* node) const {

        }

        void PrintVisitor::visit(const StatementList* node) const {

        }

        void PrintVisitor::visit(const MoveStatement* node) const {

        }

        void PrintVisitor::visit(const ExpStatement* node) const {

        }

        void PrintVisitor::visit(const JumpStatement* node) const {

        }

        void PrintVisitor::visit(const CondJumpStatement* node) const {

        }

        void PrintVisitor::visit(const SeqStatement* node) const {

        }

        void PrintVisitor::visit(const LabelStatement* node) const {

        }
    }
}
