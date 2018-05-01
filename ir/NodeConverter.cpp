//
// Created by ksenull on 5/1/18.
//
#include "NodeConverter.h"

namespace ir {
    namespace translate {

        const tree::IExpression* CExpConverter::ToExp() const {
            return nullptr;
        }

        const tree::IStatement* CExpConverter::ToStm() const {
            return nullptr;
        }

        const tree::IStatement* CExpConverter::ToConditional(const Label* ifLabel, const Label* elseLabel) const {
            return nullptr;
        }

        

        const tree::IExpression* CStmConverter::ToExp() const {
            return nullptr;
        }

        const tree::IStatement* CStmConverter::ToStm() const {
            return nullptr;
        }

        const tree::IStatement* CStmConverter::ToConditional(const Label* ifLabel, const Label* elseLabel) const {
            return nullptr;
        }

        
        
        const tree::IExpression* CCondStmConverter::ToExp() const {
            return nullptr;
        }

        const tree::IStatement* CCondStmConverter::ToStm() const {
            return nullptr;
        }

        const tree::IStatement* CCondStmConverter::ToConditional(const Label* ifLabel, const Label* elseLabel) const {
            return nullptr;
        }
    }
}
