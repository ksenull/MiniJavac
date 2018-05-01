#pragma once

#include "Statements.h"

namespace ir {
    namespace translate {

        struct ISubtreeWrapper {
            virtual ~ISubtreeWrapper() = default;

            virtual const tree::IExpression* ToExp() const = 0;
            virtual const tree::IStatement* ToStm() const = 0;
            virtual const tree::IStatement* ToConditional(const Label* ifLabel, const Label* elseLabel) const = 0;
        };

        class CExpConverter : public ISubtreeWrapper {
        public:
            explicit CExpConverter(const tree::IExpression* exp) : exp(exp) {}

            ~CExpConverter() override = default;

            const tree::IExpression* ToExp() const override;

            const tree::IStatement* ToStm() const override;

            const tree::IStatement* ToConditional(const Label* ifLabel, const Label* elseLabel) const override;

        private:
            const tree::IExpression* exp;
        };

        class CStmConverter : public ISubtreeWrapper {
        public:
            explicit CStmConverter(const tree::IStatement* stm) : stm(stm) {}

            ~CStmConverter() override = default;

            const tree::IExpression* ToExp() const override;

            const tree::IStatement* ToStm() const override;

            const tree::IStatement* ToConditional(const Label* ifLabel, const Label* elseLabel) const override;

        private:
            const tree::IStatement* stm;
        };

        class CCondStmConverter : public ISubtreeWrapper {
        public:
            explicit CCondStmConverter(const tree::CondJumpStatement* condStm) : condStm(condStm) {}

            ~CCondStmConverter() override = default;

            const tree::IExpression* ToExp() const override;

            const tree::IStatement* ToStm() const override;

            const tree::IStatement* ToConditional(const Label* ifLabel, const Label* elseLabel) const override;

        private:
            const tree::CondJumpStatement* condStm;
        };
    }
}