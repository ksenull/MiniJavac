//
// Created by ksenull on 3/4/18.
//

#include "Nodes.h"

namespace ast {
    namespace nodes {

        DEFINE_PRINT_ACCEPT(Program)

        MainClass* Program::getMainClass() const {
            return mainClass;
        }

        ClassDeclarationList* Program::getClassDeclarationList() const {
            return classDeclarationList;
        }

    }
}