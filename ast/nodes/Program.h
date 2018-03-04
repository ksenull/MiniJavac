#pragma once

#include "Node.h"
#include "MainClass.h"

namespace ast {
    namespace nodes {

        class Program : public Node {
            MainClass* mainClass;

        public:
            Program(MainClass* _mainClass);

            DECLARE_ACCEPT(Program)
        };

    }
}