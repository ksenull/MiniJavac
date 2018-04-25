#pragma once

#include "../../symboltable/Symbol.h"

namespace ast {
    namespace nodes {

        struct Identifier : symboltable::Symbol {
//            std::string name;

            Identifier() = default;

            /* implicit */ Identifier(std::string&& name) : Symbol(std::move(name)) {}

            /* implicit */ Identifier(const char* name) : Symbol(name) {}

            void accept(const IVisitor<void>* visitor) const {
                visitor->visit(this);
            }
        };
    }
}