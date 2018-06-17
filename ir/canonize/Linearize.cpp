#include <algorithm>
#include "Linearize.h"
#include "Reorder.h"

namespace ir {

    namespace tree {
        bool IsConstExpression(IExpression* expr) {
            return dynamic_cast<CConstExpression*>(expr)
                   || dynamic_cast<CNameExpression*>(expr);
        };

        bool Commute(CExpressionList* exprs, IStatement* stmt);

        bool Commute(IExpression* expr, IStatement* stmt) {
            if (auto seq = dynamic_cast<CSeqStatement*>(stmt)) {
                if (!Commute(expr, seq->left) || !Commute(expr, seq->right)) {
                    return false;
                }
                return true;
            }
            if (auto exp = dynamic_cast<CExpStatement*>(stmt)) {
                if (IsConstExpression(exp->exp)) {
                    return true;
                }
            }
            if (IsConstExpression(expr)) {
                return true;
            }
            if (!Commute(ExtractExpressions(expr), stmt)) {
                return false;
            }
            return true;
        }

        bool Commute(CExpressionList* exprs, IStatement* stmt) {
            for (auto* expr : exprs->nodes) {
                if (!Commute(dynamic_cast<IExpression*>(expr), stmt)) {
                    return false;
                }
            }
            return true;
        }

        struct CStmExp {
            CStmExp() : stmRoot(nullptr), exprs(new CExpressionList) {};
            IStatement* stmRoot;
            CExpressionList* exprs;
        };

        IStatement* CanonizeStatement(IStatement* stmt);

        CEseqExpression* CanonizeExpression(IExpression* expr);

        CStmExp ExtractEseqAndSplit(CExpressionList* args) {
            // extract eseq from args and pull side-effects stms to separate list that should be executed before explist
            std::vector<CEseqExpression*> eseqExps;
            for (auto* rawArg : args->nodes) {
                if (auto* call = dynamic_cast<CCallExpression*>(rawArg)) {  // moving calls to top level
                    // Memoize return value
                    auto temp = new CTempExpression(new TempReg());
                    rawArg = new CEseqExpression(new CMoveStatement(temp, call), temp);
                }
                auto* canonizedArg = CanonizeExpression(dynamic_cast<IExpression*>(rawArg));
                eseqExps.emplace_back(canonizedArg); // continue canonization
            }

            CStmExp result;
            for (long i = eseqExps.size() - 1; i >= 0; i--) {
                // чтобы образовать дерево из SEQ конструкций идем с конца и формируем его, при этом exps вставляются в обратном порядке
                IStatement* stm;
                if (Commute(result.exprs, eseqExps[i]->stm)) {
                    stm = eseqExps[i]->stm;
                    result.exprs->nodes.emplace_back(eseqExps[i]->exp);
                } else {
                    auto temp = new CTempExpression(
                            new TempReg); // [ESEQ(s, e1), e2, e3] -> (s, MOVE(TEMP_t, e1)) ; [TEMP_t, e2, e3]
                    stm = eseqExps[i]->stm;
                    stm = new CSeqStatement(stm, new CMoveStatement(temp, eseqExps[i]->exp));
                    result.exprs->nodes.emplace_back(temp);
                }
                if (!result.stmRoot) {
                    result.stmRoot = stm;
                } else {
                    result.stmRoot = new CSeqStatement(stm, result.stmRoot);
                }
            }
            std::reverse(result.exprs->nodes.begin(), result.exprs->nodes.end()); // разворачиваем exps в исходный порядок
            return result;
        }

        IStatement* PurifyStatement(IStatement* stmt) {
            auto exps = ExtractExpressions(stmt);
            auto purifiedExps = ExtractEseqAndSplit(exps);
            if (purifiedExps.stmRoot == nullptr) {
                return ProcessStm(stmt, purifiedExps.exprs);
            }
            return new CSeqStatement(purifiedExps.stmRoot, ProcessStm(stmt, purifiedExps.exprs));
        }

        CEseqExpression* PurifyExpression(IExpression* expr) {
            auto* extracted = ExtractExpressions(expr);
            auto purifiedExpressions = ExtractEseqAndSplit(extracted);
            return new CEseqExpression(purifiedExpressions.stmRoot, ProcessExp(expr, purifiedExpressions.exprs));
        }

        CSeqStatement* CanonizeStatement(CSeqStatement* seq) {
            auto* left = CanonizeStatement(seq->left);
            auto* right = CanonizeStatement(seq->right);
            return new CSeqStatement(left, right);
        }

        IStatement* CanonizeStatement(CMoveStatement* move) {
            if (auto eseq = dynamic_cast<const CEseqExpression*>(move->target)) {  // MOVE(ESEQ(s,e1),e2) -> SEQ(s, MOVE(e1,e2))
                auto seq = new CSeqStatement(
                        eseq->stm,
                        new CMoveStatement(eseq->exp, move->source)
                );
                return CanonizeStatement(seq);
            }
            return PurifyStatement(move);
        }

        IStatement* CanonizeStatement(IStatement* stmt) {
            if (auto* seq = dynamic_cast<CSeqStatement*>(stmt)) {
                return CanonizeStatement(seq);
            } else if (auto* move = dynamic_cast<CMoveStatement*>(stmt)) {
                return CanonizeStatement(move);
            }
            return PurifyStatement(stmt);
        }

        CEseqExpression* CanonizeExpression(IExpression* expr) {
            if (auto eseq = dynamic_cast<const CEseqExpression*>(expr)) {
                auto oldSideEffect = CanonizeStatement(eseq->stm);
                auto reordered = CanonizeExpression(eseq->exp);
                return new CEseqExpression(new CSeqStatement(oldSideEffect, reordered->stm), reordered->exp);
            }
            return PurifyExpression(expr);
        }

        void LinearizeCanonized(IStatement* stmt, CStatementList& result) {
            if (auto seq = dynamic_cast<const CSeqStatement*>(stmt)) {
                if (seq->left) LinearizeCanonized(seq->left, result);
                if (seq->right) LinearizeCanonized(seq->right, result);
            } else {
                result.nodes.emplace_back(stmt);
            }
        }

        CStatementList Linearize(IStatement* stmt) {
            auto result = CStatementList{};
            LinearizeCanonized(CanonizeStatement(stmt), result);
            return result;
        }

    } //tree
} //ir