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
            DECLARE_PRINT_VISIT(CConstExpression);
            DECLARE_PRINT_VISIT(CNameExpression);
            DECLARE_PRINT_VISIT(CTempExpression);
            DECLARE_PRINT_VISIT(CBinopExpression);
            DECLARE_PRINT_VISIT(CMemExpression);
            DECLARE_PRINT_VISIT(CCallExpression);
            DECLARE_PRINT_VISIT(CEseqExpression);

            DECLARE_PRINT_VISIT(CStatementList);
            DECLARE_PRINT_VISIT(CMoveStatement);
            DECLARE_PRINT_VISIT(CExpStatement);
            DECLARE_PRINT_VISIT(CJumpStatement);
            DECLARE_PRINT_VISIT(CCondJumpStatement);
            DECLARE_PRINT_VISIT(CSeqStatement);
            DECLARE_PRINT_VISIT(CLabelStatement);
#undef DECLARE_PRINT_VISIT
        private:
            mutable std::ofstream fout;
        };
    }
}