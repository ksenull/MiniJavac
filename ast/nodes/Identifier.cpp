//
// Created by ksenull on 3/4/18.
//

#include "Identifier.h"

namespace ast {
    namespace nodes {

        Identifier::Identifier(std::string _name) : name(_name){}

        void Identifier::accept(IVisitor* visitor) const {
            visitor->visit(this);
        }

        std::string& Identifier::getName() const {
            return name;
        }
    }
}
