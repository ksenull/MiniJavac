#pragma once

#include <iostream>
#include <fstream>
#include "IVisitor.h"

namespace ir {
    namespace tree {
        
        class PrintVisitor : public  IVisitor<void> {
        public:
            PrintVisitor() = default;

            explicit PrintVisitor(const std::string& fout);
            ~PrintVisitor() = default;

            void finish();

#define DECLARE_PRINT_VISIT(NODE)  void visit(const NODE* node) const;
            DECLARE_PRINT_VISIT(CExpressionList);
            DECLARE_PRINT_VISIT(ConstExpression);
            DECLARE_PRINT_VISIT(NameExpression);
            DECLARE_PRINT_VISIT(TempExpression);
            DECLARE_PRINT_VISIT(BinopExpression);
            DECLARE_PRINT_VISIT(MemExpression);
            DECLARE_PRINT_VISIT(CallExpression);
            DECLARE_PRINT_VISIT(EseqExpression);

            DECLARE_PRINT_VISIT(StatementList);
            DECLARE_PRINT_VISIT(MoveStatement);
            DECLARE_PRINT_VISIT(ExpStatement);
            DECLARE_PRINT_VISIT(JumpStatement);
            DECLARE_PRINT_VISIT(CondJumpStatement);
            DECLARE_PRINT_VISIT(SeqStatement);
            DECLARE_PRINT_VISIT(LabelStatement);
#undef DECLARE_PRINT_VISIT
        private:
            mutable std::ofstream fout;
        };
    }
}