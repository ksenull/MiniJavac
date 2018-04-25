//
// Created by ksenull on 4/25/18.
//
#include "VariableInfo.h"

namespace symboltable {

    VariableInfo::VariableInfo(ast::nodes::VariableDeclaration* var) : IInfo(var->loc) {

    }
}
