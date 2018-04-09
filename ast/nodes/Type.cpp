//
// Created by ksenull on 4/9/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(Type)

        const std::string& Type::get() const {
            return id.getName();
        }
    }
}