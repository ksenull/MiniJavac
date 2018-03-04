//
// Created by ksenull on 3/4/18.
//

#include "Program.h"

namespace ast {
    namespace nodes {

        Program::Program(MainClass* _mainClass) : mainClass(_mainClass) {}

        DEFINE_PRINT_ACCEPT(Program)
    }
}