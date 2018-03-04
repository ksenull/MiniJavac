#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {

        class MainClass;

        class Program : public Node {
            MainClass* mainClass;

        public:
            Program(MainClass* _mainClass);

            DECLARE_PRINT_ACCEPT(Program)
        };

    }
}