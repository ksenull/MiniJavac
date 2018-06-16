#pragma once

#include "../tree/Statements.h"

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
            CCondStmConverter() = default;
            CCondStmConverter(tree::IExpression* left, tree::RelationalOperation op, tree::IExpression* right) :
            op(op), left(left), right(right) {}
            ~CCondStmConverter() override = default;

            tree::IExpression* ToExp() const override;

            tree::IStatement* ToStm() const override;

            tree::IStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;
        private:
            tree::RelationalOperation op;
            tree::IExpression* left;
            tree::IExpression* right;
        };

        // shorten conditions
        class CFromAndConverter : public CCondStmConverter {
        public:
            CFromAndConverter(tree::IExpression* left, tree::IExpression* right) : left(left), right(right) {}

            tree::CondJumpStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;
        private:
            tree::IExpression* left;
            tree::IExpression* right;
        };

        class CFromOrConverter : public CCondStmConverter {
        public:
            CFromOrConverter(tree::IExpression* left, tree::IExpression* right) : left(left), right(right) {}

            tree::CondJumpStatement* ToConditional(const Label& ifLabel, const Label& elseLabel) const override;
        private:
            tree::IExpression* left;
            tree::IExpression* right;
        };
    }
}