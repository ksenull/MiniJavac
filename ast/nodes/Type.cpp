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

        TypeType Type::getTt() const {
            return tt;
        }

        const Identifier& Type::getId() const {
            return id;
        }
    }
}