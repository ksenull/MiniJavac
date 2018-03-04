//
// Created by ksenull on 3/4/18.
//

#include "Identifier.h"

#include <utility>

namespace ast {
    namespace nodes {

        Identifier::Identifier(std::string _name) : name(std::move(_name)){}

        DEFINE_ACCEPT(Identifier)

        std::string& Identifier::getName() const {
            return name;
        }
    }
}
