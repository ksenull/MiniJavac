#include "Reorder.h"

#include <cassert>


namespace ir {
    namespace tree {
        CExpressionList* ExtractExpressions(INode* node) {
            if (auto* move = dynamic_cast<CMoveStatement*>(node)) {
                // Call memoization pattern
                auto temp = dynamic_cast<CTempExpression*>(move->target);
                auto call = dynamic_cast<CCallExpression*>(move->source);
                if (temp && call) {
                    return ExtractExpressions(call);
                }

                auto* ret = new CExpressionList();
                if (auto mem = dynamic_cast<CMemExpression*>(move->target)) {
                    ret->nodes.emplace_back(mem->addr);
                }
                ret->nodes.emplace_back(move->source);
                return ret;
            }
            if (auto* exp = dynamic_cast<CExpStatement*>(node)) {
                // ExpCall pattern
                if (auto call = dynamic_cast<CCallExpression*>(exp->exp)) {
                    return ExtractExpressions(call);
                }

                return new CExpressionList{{exp->exp}};
            }
            if (auto* cond = dynamic_cast<CCondJumpStatement*>(node)) {
                return new CExpressionList{{cond->left, cond->right}};
            }
            if (auto* binop = dynamic_cast<CBinopExpression*>(node)) {
                return new CExpressionList{{binop->left, binop->right}};
            }
            if (auto* mem = dynamic_cast<CMemExpression*>(node)) {
                return new CExpressionList{{mem->addr}};
            }
            if (auto* call = dynamic_cast<CCallExpression*>(node)) {
                return call->args;
            }
            if (auto* eseq = dynamic_cast<CEseqExpression*>(node)) {
                return new CExpressionList{{eseq->exp}};
            }
            return new CExpressionList();
        }

        IExpression* ProcessExp(IExpression* expr, CExpressionList* expsExtracted) {
            if (auto* binop = dynamic_cast<CBinopExpression*>(expr)) {
                return new CBinopExpression(dynamic_cast<IExpression*>(expsExtracted->nodes[0]), binop->op,
                                            dynamic_cast<IExpression*>(expsExtracted->nodes[1]));
            }
            if (auto* mem = dynamic_cast<CMemExpression*>(expr)) {
                return new CMemExpression(dynamic_cast<IExpression*>(expsExtracted->nodes[0]));
            }
            if (auto* call = dynamic_cast<CCallExpression*>(expr)) {
                return new CCallExpression(call->func, expsExtracted);
            }
            if (auto* eseq = dynamic_cast<CEseqExpression*>(expr)) {
                return new CEseqExpression(eseq->stm, dynamic_cast<IExpression*>(expsExtracted->nodes[0]));
            }

            assert(expsExtracted->nodes.empty());
            return expr;
        }

        IStatement* ProcessStm(IStatement* stmt, CExpressionList* expsExtracted) {
            if (auto* move = dynamic_cast<CMoveStatement*>(stmt)) {
                auto temp = dynamic_cast<CTempExpression*>(move->target);
                auto call = dynamic_cast<CCallExpression*>(move->source);
                if (temp && call) {
                    auto* callExp = ProcessExp(call, expsExtracted);
                    return new CMoveStatement(temp, callExp);  // ok, going to children
                }

                if (dynamic_cast<const CMemExpression*>(move->target)) {
                    assert(2U == expsExtracted->nodes.size());
                    return new CMoveStatement(new CMemExpression(dynamic_cast<IExpression*>(expsExtracted->nodes[0])),
                                              dynamic_cast<IExpression*>(expsExtracted->nodes[1]));
                }

                assert(1U == expsExtracted->nodes.size());
                return new CMoveStatement(move->target, dynamic_cast<IExpression*>(expsExtracted->nodes[0]));
            }

            if (auto* exp = dynamic_cast<CExpStatement*>(stmt)) {
                // ExpCall pattern
                if (auto* call = dynamic_cast<CCallExpression*>(exp->exp)) {
                    return new CExpStatement(ProcessExp(call, expsExtracted));
                }

                return new CExpStatement(dynamic_cast<IExpression*>(expsExtracted->nodes[0]));
            }

            if (auto* cond = dynamic_cast<CCondJumpStatement*>(stmt)) {
                return new CCondJumpStatement(dynamic_cast<IExpression*>(expsExtracted->nodes[0]), cond->op,
                                              dynamic_cast<IExpression*>(expsExtracted->nodes[1]), cond->ifTarget, cond->elseTarget);
            }

            assert(expsExtracted->nodes.empty());
            return stmt;
        }
    } //tree
} //ir