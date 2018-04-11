//
// Created by ksenull on 4/9/18.
//
#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(ClassDeclaration)

        DEFINE_PRINT_ACCEPT(ClassDeclarationList)

        const Identifier& ClassDeclaration::getId() const {
            return id;
        }

        const Identifier& ClassDeclaration::getBase() const {
            return base;
        }

        VariableDeclarationStatementList* ClassDeclaration::getLocalVars() const {
            return localVars;
        }

        MethodDeclarationList* ClassDeclaration::getMethods() const {
            return methods;
        }

    }
}
