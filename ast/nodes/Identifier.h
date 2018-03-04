#pragma once

#include <iostream>

#include "../IVisitor.h"
#include "Node.h"

namespace ast {
    namespace nodes {

        class Identifier : public Node{
            std::string name;

        public:
            Identifier(std::string _name);
            void accept(IVisitor* visitor) const;

            std::string& getName() const;
        };

    }
}