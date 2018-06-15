#pragma once

#include "../../symboltable/Symbol.h"

namespace ast {
    namespace nodes {

        struct Identifier {
            std::string name;

            Identifier() = default;

            /* implicit */ Identifier(const std::string& name) : name(name) {}

            /* implicit */ Identifier(std::string&& name) : name(std::move(name)) {}

            /* implicit */ Identifier(const char* name) : name(name) {}

            void accept(const IVisitor<void>* visitor) const {
                visitor->visit(this);
            }

            ir::translate::ISubtreeWrapper* accept(const IVisitor<ir::translate::ISubtreeWrapper*>* visitor) const {
                return visitor->visit(this);
            }
        };
    }
}