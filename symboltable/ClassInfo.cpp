//
// Created by ksenull on 4/25/18.
//
#include "ClassInfo.h"
#include "../ast/nodes/Nodes.h"

namespace symboltable {
    ClassInfo::ClassInfo(ast::nodes::MainClass* mainClass) : IInfo(mainClass->loc) {
        Symbol symbol(mainClass->name);
    }
    ClassInfo::ClassInfo(ast::nodes::INode* node) : IInfo(node->loc) {

    }
}
