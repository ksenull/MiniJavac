//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(Identifier)

        const std::string& Identifier::getName() const {
            return name;
        }
    }
}
