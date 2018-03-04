//
// Created by ksenull on 3/4/18.
//

#include "Identifier.h"

namespace ast {
    namespace nodes {

        Identifier::Identifier(std::string _name) : name(std::move(_name)){}

        DEFINE_PRINT_ACCEPT(Identifier)

        const std::string& Identifier::getName() const {
            return name;
        }
    }
}
