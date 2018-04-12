#include <iostream>
#include <fstream>
#include "PrintVisitor.h"
#include "../grammar/parse.h"
#include "nodes/Nodes.h"
//#include "GraphV.h"

static const std::string PathPrefix = "/home/ksenull/workspace/minijavac_17/";

int main() {
    ast::nodes::Program* program;
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/BinaryTree.java",std::ios::in)) {
        std::istream in(&fb);
        program = Grammar::Parse(in);
        auto* visitor = new ast::PrintVisitor(PathPrefix + "ast/graph.dot");

        program->accept(visitor);
        visitor->finish();
    }
//        program = Grammar::ParseCin();
    return 0;
}