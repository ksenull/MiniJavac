//
// Created by ksenull on 4/9/18.
//
#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(VariableDeclarationStatementList)
        DEFINE_PRINT_ACCEPT(VariableDeclarationStatement)
        DEFINE_PRINT_ACCEPT(VariableDeclaration)


        const Identifier& VariableDeclaration::getId() const {
            return id;
        }

        Type* VariableDeclaration::getType() const {
            return type;
        }
    }
}