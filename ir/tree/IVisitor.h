#pragma once

namespace ir {

    namespace tree {

        struct CExpressionList;
        struct CConstExpression;
        struct CNameExpression;
        struct CTempExpression;
        struct CBinopExpression;
        struct CMemExpression;
        struct CCallExpression;
        struct CEseqExpression;

        struct CStatementList;
        struct CMoveStatement;
        struct CExpStatement;
        struct CJumpStatement;
        struct CCondJumpStatement;
        struct CSeqStatement;
        struct CLabelStatement;


        template<typename T>
        class IVisitor {
        public:
#define DECLARE_IVISIT(NODE) virtual T visit(const NODE* node) const = 0;

            DECLARE_IVISIT(CExpressionList);
            DECLARE_IVISIT(CConstExpression);
            DECLARE_IVISIT(CNameExpression);
            DECLARE_IVISIT(CTempExpression);
            DECLARE_IVISIT(CBinopExpression);
            DECLARE_IVISIT(CMemExpression);
            DECLARE_IVISIT(CCallExpression);
            DECLARE_IVISIT(CEseqExpression);

            DECLARE_IVISIT(CStatementList);
            DECLARE_IVISIT(CMoveStatement);
            DECLARE_IVISIT(CExpStatement);
            DECLARE_IVISIT(CJumpStatement);
            DECLARE_IVISIT(CCondJumpStatement);
            DECLARE_IVISIT(CSeqStatement);
            DECLARE_IVISIT(CLabelStatement);

#undef DECLARE_IVISIT
        };
    }
}
