#include <iostream>
#include <fstream>
#include "PrintVisitor.h"
#include "../grammar/parse.h"
#include "nodes/Nodes.h"


int main() {
    ast::nodes::Program* program;
    std::filebuf fb;
    if (fb.open ("/home/ksenull/workspace/minijavac_17/Samples/BinaryTree.java",std::ios::in)) {
        std::istream in(&fb);
        program = Grammar::Parse(in);
        auto* visitor = new ast::PrintVisitor();
        program->accept(visitor);
        visitor->graph.savePng("/home/ksenull/workspace/minijavac_17/graph.png");
        visitor->graph.release();
    }
//        program = Grammar::ParseCin();
    return 0;
}