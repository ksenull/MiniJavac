#include "FASMCodegen.h"

#include "FASMOperand.h"
#include "../../common/Exception.h"
#include "../../ir/tree/Statements.h"

namespace codegen {
    namespace fasm {

        struct CodegenError : common::MiniJavacException {
            CodegenError() : common::MiniJavacException("Codegen error") {};
        };

        namespace irt = ir::tree;

        std::string BinOpInstruction(irt::BinaryOperation op) {
            switch (op) {
                case irt::BO_Plus:
                    return "add";
                case irt::BO_Minus:
                    return "sub";
                case irt::BO_Mul:
                    return "imul";
                case irt::BO_And:
                    return "and";
                case irt::BO_Or:
                    return "or";
                case irt::BO_Xor:
                    return "xor";
                default:
                    return "not_implemented";
            };
        }

        std::string CompareJump(irt::RelationalOperation op) {
            switch (op) {
                case irt::RO_Eq:
                    return "je";
                case irt::RO_Ne:
                    return "jne";
                case irt::RO_Lt:
                    return "jl";
                case irt::RO_Gt:
                    return "jg";
                case irt::RO_Le:
                    return "jle";
                case irt::RO_Ge:
                    return "jge";
                default:
                    return "not_implemented";
            }
        }

        IOperand* CCodegen::munchExp(irt::IExpression* exp) {
            if (auto* constExp = dynamic_cast<irt::CConstExpression*>(exp)) {
                return new CConstOperand(constExp->i);
            }
            if (auto* name = dynamic_cast<irt::CNameExpression*>(exp)) {
                return new CConstOperand(name->label.name);
            }
            if (auto* temp = dynamic_cast<irt::CTempExpression*>(exp)) {
                return new CInRegisterOperand(temp);
            }
            if (auto* binop = dynamic_cast<irt::CBinopExpression*>(exp)) {
                auto res = new CInRegisterOperand();
                auto left = munchExp(binop->left);
                auto right = munchExp(binop->right);
                AddMoveInstruction(*res, *left, result);
                AddBinaryInstruction(BinOpInstruction(binop->op), *res, *right, result, ReadWriteUsage);
                return res;
            }
            if (auto* mem = dynamic_cast<irt::CMemExpression*>(exp)) {
                if (auto binop = dynamic_cast<const irt::CBinopExpression*>(mem->addr)) {
                    if (binop->op == irt::BO_Plus) {
                        auto left = binop->left;
                        auto right = binop->right;

                        if (dynamic_cast<const irt::CConstExpression*>(left)) {
                            auto tmp = left;
                            left = right;
                            right = tmp;
                        }

                        if (auto rightCon = dynamic_cast<const irt::CConstExpression*>(right)) {
                            return new CInMemoryOperand(munchExp(left)->ToLoadedOperand(result), rightCon->i);
                        }
                    }
                }
                auto tempAddress = munchExp(mem->addr)->ToLoadedOperand(result);
                return new CInMemoryOperand(tempAddress);
            }
            if (auto* call = dynamic_cast<irt::CCallExpression*>(exp)) {
                result.emplace_back(MakeInstruction("push\t0"));
                for (auto* arg : call->args->nodes) {
                    if (auto* argExp = dynamic_cast<irt::IExpression*>(arg)) {
                        auto* oper = munchExp(argExp);
                        auto inst = MakeInstruction("push").Src(*oper);
                        result.emplace_back(inst);
                    }
                }
                result.emplace_back(MakeInstruction("call\t" + call->func->name));
                result.emplace_back(MakeInstruction("add\t\tesp," + std::to_string(frame->GetWordSize() * call->args->nodes.size())));
                auto ret = new CInRegisterOperand();
                result.push_back(MakeInstruction("pop").Dst(*ret));
                return ret;
            }
            if (auto* eseq = dynamic_cast<irt::CEseqExpression*>(exp)) {
                throw CodegenError();
            }
            throw CodegenError();
        }

        void CCodegen::munchStm(irt::IStatement* stm) {
            if (auto* move = dynamic_cast<irt::CMoveStatement*>(stm)) {
                auto dst = munchExp(move->target);
                auto src = munchExp(move->source);
                AddMoveInstruction(*dst, *src, result);
            }
            if (auto* exp = dynamic_cast<irt::CExpStatement*>(stm)) {
                munchExp(exp->exp);
            }
            if (auto* jump = dynamic_cast<irt::CJumpStatement*>(stm)) {
                result.emplace_back(MakeInstruction("jmp\t\t" + jump->target.name).AddJump(jump->target));
            }
            if (auto* cond = dynamic_cast<irt::CCondJumpStatement*>(stm)) {
                auto left = munchExp(cond->left);
                auto right = munchExp(cond->right);
                AddBinaryInstruction("cmp", *left, *right, result, ReadUsage);
                result.emplace_back(MakeInstruction(CompareJump(cond->op) + "\t" + cond->ifTarget.name).AddJump(cond->ifTarget).AddJump(cond->elseTarget));
            }
            if (auto* seq = dynamic_cast<irt::CSeqStatement*>(stm)) {
                throw CodegenError();
            }
            if (auto* label = dynamic_cast<irt::CLabelStatement*>(stm)) {
                result.emplace_back(MakeLabelInstruction(&label->label));
            }
        }


        CInstructionList CCodegen::Gen(ir::IFrame* _frame, irt::IStatement* stmt) {
            frame = _frame;
            result.emplace_back(MakeInstruction("---"));  // debuginfo
            munchStm(stmt);
            return result;
        }

    }
}