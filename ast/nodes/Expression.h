#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {

        class Expression : public Node {

        };


        class BinaryExpression : public Expression {
            Expression* left;
            Expression* right;
        public:
            BinaryExpression(Expression* _left, Expression* _right) : left(_left), right(_right) {}

        };


#define DEFINE_BINARY_EXP(NAME) \
        class NAME : public BinaryExpression { \
        public: \
            NAME(Expression* _left, Expression* _right) : BinaryExpression(_left, _right) {} \
            DECLARE_PRINT_ACCEPT(NAME) \
        };

        DEFINE_BINARY_EXP(And)
        DEFINE_BINARY_EXP(Less)
        DEFINE_BINARY_EXP(Plus)
        DEFINE_BINARY_EXP(Minus)
        DEFINE_BINARY_EXP(Mult)

#undef DEFINE_BINARY_EXP

    }
}
