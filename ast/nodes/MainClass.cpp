//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(MainClass)

        const Identifier& MainClass::getArgsName() const {
            return argsName;
        }

        Statement* MainClass::getSt() const {
            return st;
        }
    }
}