#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {

        class Identifier;
        class Statement;


        class MainClass : Node {
            Identifier* className;
            Identifier* argsName;
            Statement* st;
        public:
            MainClass(Identifier* id1, Identifier* id2, Statement* _st);

            DECLARE_PRINT_ACCEPT(MainClass)
        };
    }
}
