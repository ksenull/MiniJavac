#pragma once

#include "Node.h"
#include "MainClass.h"

namespace ast {
    namespace nodes {

        class Program : public Node {
            MainClass mainClass;

        public:
            Program(const MainClass& _mainClass);

            void accept(IVisitor* visitor) const;
        };

    }
}