//
// Created by ksenull on 3/4/18.
//

#include "Statement.h"

namespace ast {
    namespace nodes {

        DEFINE_ACCEPT(Assign)

        DEFINE_ACCEPT(IfElse)

        DEFINE_ACCEPT(While)

        DEFINE_ACCEPT(Print)

        DEFINE_ACCEPT(GetItem)
    }
}