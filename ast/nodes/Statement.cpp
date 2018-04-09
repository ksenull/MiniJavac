//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(StatementList)
        DEFINE_PRINT_ACCEPT(NestedStatement)
        DEFINE_PRINT_ACCEPT(IfStatement)
        DEFINE_PRINT_ACCEPT(WhileStatement)
        DEFINE_PRINT_ACCEPT(PrintStatement)
        DEFINE_PRINT_ACCEPT(AssignStatement)
        DEFINE_PRINT_ACCEPT(ArrayAssignStatement)
    }
}