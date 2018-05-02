#pragma once

namespace ir {

    namespace tree {

        struct CExpressionList;
        struct ConstExpression;
        struct NameExpression;
        struct TempExpression;
        struct BinopExpression;
        struct MemExpression;
        struct CallExpression;
        struct EseqExpression;

        struct StatementList;
        struct MoveStatement;
        struct ExpStatement;
        struct JumpStatement;
        struct CondJumpStatement;
        struct SeqStatement;
        struct LabelStatement;


        template<typename T>
        class IVisitor {
        public:
#define DECLARE_IVISIT(NODE) virtual T visit(const NODE* node) const = 0;

            DECLARE_IVISIT(CExpressionList);
            DECLARE_IVISIT(ConstExpression);
            DECLARE_IVISIT(NameExpression);
            DECLARE_IVISIT(TempExpression);
            DECLARE_IVISIT(BinopExpression);
            DECLARE_IVISIT(MemExpression);
            DECLARE_IVISIT(CallExpression);
            DECLARE_IVISIT(EseqExpression);

            DECLARE_IVISIT(StatementList);
            DECLARE_IVISIT(MoveStatement);
            DECLARE_IVISIT(ExpStatement);
            DECLARE_IVISIT(JumpStatement);
            DECLARE_IVISIT(CondJumpStatement);
            DECLARE_IVISIT(SeqStatement);
            DECLARE_IVISIT(LabelStatement);

#undef DECLARE_IVISIT
        };
    }
}
