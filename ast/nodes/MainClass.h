#pragma once

#include "Node.h"
#include "Statement.h"
#include "Identifier.h"

namespace ast {
    namespace nodes {
        class MainClass : Node {
            Identifier* className;
            Identifier* argsName;
            Statement* st;
        public:
            MainClass(Identifier* id1, Identifier* id2, Statement* _st);

            DECLARE_ACCEPT(MainClass)
        };
    }
}
