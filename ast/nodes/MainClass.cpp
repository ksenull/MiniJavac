//
// Created by ksenull on 3/4/18.
//

#include "MainClass.h"

namespace ast {
    namespace nodes {

        MainClass::MainClass(Identifier* id1, Identifier* id2, Statement* _st) :
        className(id1), argsName(id2), st(_st){}

        DEFINE_PRINT_ACCEPT(MainClass)
    }
}