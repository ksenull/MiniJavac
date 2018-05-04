#include <iostream>
#include <fstream>
#include "PrintVisitor.h"
#include "../grammar/parse.h"
#include "nodes/Nodes.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "BadSamples/TC_1a.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
        auto* visitor = new ast::PrintVisitor(PathPrefix + "ast/graph.dot");
        program.accept(visitor);
        visitor->finish();
    }
//        program = Grammar::ParseCin();
    return 0;
}