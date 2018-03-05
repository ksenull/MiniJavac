//
// Created by ksenull on 3/4/18.
//

#include "Statement.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(Assign)

        DEFINE_PRINT_ACCEPT(IfElse)

        DEFINE_PRINT_ACCEPT(While)

        DEFINE_PRINT_ACCEPT(Print)

        DEFINE_PRINT_ACCEPT(SetItem)
    }
}