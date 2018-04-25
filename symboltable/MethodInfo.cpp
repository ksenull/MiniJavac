//
// Created by ksenull on 4/25/18.
//
#include "MethodInfo.h"

namespace symboltable {
    
    MethodInfo::MethodInfo(ast::nodes::MethodDeclaration* methodDeclaration) : IInfo(methodDeclaration->loc) {
        
    }
}
