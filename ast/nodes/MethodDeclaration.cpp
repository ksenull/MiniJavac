//
// Created by ksenull on 4/9/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {
        DEFINE_PRINT_ACCEPT(MethodDeclarationList)
        DEFINE_PRINT_ACCEPT(MethodDeclaration)

        const Identifier& MethodDeclaration::getId() const {
            return id;
        }

        Type* MethodDeclaration::getReturnType() const {
            return returnType;
        }

        Expression* MethodDeclaration::getReturnExp() const {
            return returnExp;
        }

        ArgumentDeclarationList* MethodDeclaration::getArgs() const {
            return args;
        }

        StatementList* MethodDeclaration::getSl() const {
            return sl;
        }
    }
}