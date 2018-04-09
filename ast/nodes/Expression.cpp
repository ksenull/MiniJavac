//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(BinopExpression)
        DEFINE_PRINT_ACCEPT(ArrayItemExpression)
        DEFINE_PRINT_ACCEPT(ArrayLengthExpression)
        DEFINE_PRINT_ACCEPT(CallExpression)
        DEFINE_PRINT_ACCEPT(ConstExpression)
        DEFINE_PRINT_ACCEPT(BoolExpression)
        DEFINE_PRINT_ACCEPT(IdExpression)
        DEFINE_PRINT_ACCEPT(NewArrayExpression)
        DEFINE_PRINT_ACCEPT(NewObjectExpression)
        DEFINE_PRINT_ACCEPT(NotExpression)
    }
}