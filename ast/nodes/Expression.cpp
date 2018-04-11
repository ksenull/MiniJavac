//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(BinopExpression)

        Expression* BinopExpression::getLeft() const {
            return left;
        }

        Expression* BinopExpression::getRight() const {
            return right;
        }

        BinOpType BinopExpression::getType() const {
            return type;
        }

        DEFINE_PRINT_ACCEPT(ArrayItemExpression)

        Expression* ArrayItemExpression::getExp() const {
            return exp;
        }

        Expression* ArrayItemExpression::getInd() const {
            return ind;
        }

        DEFINE_PRINT_ACCEPT(ArrayLengthExpression)

        Expression* ArrayLengthExpression::getExp() const {
            return exp;
        }

        DEFINE_PRINT_ACCEPT(CallExpression)

        Expression* CallExpression::getExp() const {
            return exp;
        }

        const Identifier& CallExpression::getMethod() const {
            return method;
        }

        ArgumentsList* CallExpression::getArgs() const {
            return args;
        }

        DEFINE_PRINT_ACCEPT(ConstExpression)

        int ConstExpression::getValue() const {
            return value;
        }

        DEFINE_PRINT_ACCEPT(BoolExpression)

        bool BoolExpression::isValue() const {
            return value;
        }

        DEFINE_PRINT_ACCEPT(IdExpression)

        const Identifier& IdExpression::getId() const {
            return id;
        }

        bool IdExpression::isThis() const {
            return isThis;
        }

        DEFINE_PRINT_ACCEPT(NewArrayExpression)

        Type* NewArrayExpression::getType() const {
            return type;
        }

        Expression* NewArrayExpression::getExp() const {
            return exp;
        }

        DEFINE_PRINT_ACCEPT(NewObjectExpression)

        const Identifier& NewObjectExpression::getId() const {
            return id;
        }

        DEFINE_PRINT_ACCEPT(NotExpression)

        Expression* NotExpression::getExp() const {
            return exp;
        }
    }
}