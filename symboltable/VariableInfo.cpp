//
// Created by ksenull on 4/25/18.
//
#include "VariableInfo.h"

namespace symboltable {

    void VariableInfo::BuildFromAst(ast::nodes::VariableDeclaration* var) {
        type = var->type;
    }
}
