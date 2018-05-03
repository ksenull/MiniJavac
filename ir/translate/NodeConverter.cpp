//
// Created by ksenull on 5/1/18.
//
#include "NodeConverter.h"
#include "../../common/Exception.h"

using BaseException = common::MiniJavacException;

namespace ir {
    namespace translate {

        using namespace tree;

        struct ConverterError : public BaseException {
            ConverterError(IExpression* from) :
                    BaseException("IR-expression couldn't be converted to IR-conditional jump statement") {}

            ConverterError(IStatement* from) :
                    BaseException("IR-statement couldn't be converted to IR-conditional jump statement") {}
        };



        IExpression* CExpConverter::ToExp() const {
            return exp;
        }

        IStatement* CExpConverter::ToStm() const {
            return new ExpStatement(exp);
        }

        IStatement* CExpConverter::ToConditional(const Label& ifLabel, const Label& elseLabel) const {
            if (auto* constExp = dynamic_cast<ConstExpression*>(exp)) {
                return new CondJumpStatement(constExp, RO_Le, new ConstExpression(0), ifLabel, elseLabel);
            }
            if (auto* nameExp = dynamic_cast<NameExpression*>(exp)) {
                return new CondJumpStatement(nameExp, RO_Ne, new NameExpression(""), ifLabel, elseLabel);
            }
            if (auto* tempExp = dynamic_cast<TempExpression*>(exp)) {
                throw ConverterError(exp);
            }
//            if (auto* binopExp) {
//
//            }
//            if (auto* memExp) {
//
//            }
//            if (auto* callExp) {
//
//            }
//            if (auto* eseqExp) {
//
//            }
            throw ConverterError(exp);
        }

        

        tree::IExpression* CStmConverter::ToExp() const {
            return new EseqExpression(stm, new ConstExpression(0));
        }

        tree::IStatement* CStmConverter::ToStm() const {
            return stm;
        }

        tree::IStatement* CStmConverter::ToConditional(const Label& ifLabel, const Label& elseLabel) const {
            if (auto* cond = dynamic_cast<CondJumpStatement*>(stm)) {
                return cond;
            }
            return nullptr;
        }

        
        
        tree::IExpression* CCondStmConverter::ToExp() const {
            return nullptr;
        }

        tree::IStatement* CCondStmConverter::ToStm() const {
            return nullptr;
        }

        tree::IStatement* CCondStmConverter::ToConditional(const Label& ifLabel, const Label& elseLabel) const {
            return nullptr;
        }

        tree::CondJumpStatement* CFromAndConverter::ToConditional(const Label& ifLabel, const Label& elseLabel) const {
            return nullptr;
        }

        tree::CondJumpStatement* CFromOrConverter::ToConditional(const Label& ifLabel, const Label& elseLabel) const {
            return nullptr;
        }
    }
}
