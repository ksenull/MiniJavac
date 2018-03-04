#pragma once

#include <iostream>
#include "Node.h"

namespace ast {
    namespace nodes {

        class Identifier : public Node{
            std::string name;

        public:
            Identifier(std::string _name);

            DECLARE_ACCEPT(Identifier)

            std::string& getName() const;
        };

    }
}