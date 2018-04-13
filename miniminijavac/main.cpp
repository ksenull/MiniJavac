#include <iostream>
#include <fstream>
#include "nodes.h"
#include "grammar/parse.h"
#include "Visitor.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/miniminijavac/";

int main() {
    ast::Program* program;
    std::filebuf fb;
    if (fb.open (PathPrefix + "Main.java",std::ios::in)) {
        std::istream in(&fb);
        program = Grammar::Parse(in);
        auto* visitor = new ast::PrintVisitor(PathPrefix + "ast/graph.dot");
//        auto& p = *program;
        program->accept(visitor);
        visitor->finish();
    }
//        program = Grammar::ParseCin();
    return 0;
}