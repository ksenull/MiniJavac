//
// Created by ksenull on 3/4/18.
//

#include "Program.h"

namespace ast {
    namespace nodes {

        Program::Program(const MainClass &_mainClass) : mainClass(_mainClass) {}

        void Program::accept(IVisitor *visitor) const {
            visitor->visit(this);
        }
    }
}