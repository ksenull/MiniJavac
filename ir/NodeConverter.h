#pragma once

#include "Statements.h"

namespace ir {
    namespace translate {

        struct ISubtreeWrapper {
            virtual ~ISubtreeWrapper() = default;

            virtual tree::IExpression* ToExp() const = 0;
            virtual tree::IStatement* ToStm() const = 0;
            virtual tree::IStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const = 0;
        };

        class CExpConverter : public ISubtreeWrapper {
        public:
            explicit CExpConverter(tree::IExpression* exp) : exp(exp) {}

            ~CExpConverter() override = default;

            tree::IExpression* ToExp() const override;

            tree::IStatement* ToStm() const override;

            tree::IStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;

        private:
            tree::IExpression* exp;
        };

        class CStmConverter : public ISubtreeWrapper {
        public:
            explicit CStmConverter(tree::IStatement* stm) : stm(stm) {}

            ~CStmConverter() override = default;

            tree::IExpression* ToExp() const override;

            tree::IStatement* ToStm() const override;

            tree::IStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;

        private:
            tree::IStatement* stm;
        };

        class CCondStmConverter : public ISubtreeWrapper {
        public:
            explicit CCondStmConverter(tree::CondJumpStatement* condStm) : condStm(condStm) {}

            ~CCondStmConverter() override = default;

            tree::IExpression* ToExp() const override;

            tree::IStatement* ToStm() const override;

            tree::IStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;

        private:
            tree::CondJumpStatement* condStm;
        };
    }
}