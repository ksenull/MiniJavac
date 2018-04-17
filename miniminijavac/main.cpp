#include <iostream>
#include <fstream>
#include <unistd.h>
#include "nodes.h"
#include "grammar/parse.h"
#include "Visitor.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/miniminijavac/";

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Main.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
        ast::PrintVisitor* visitor = new ast::PrintVisitor(PathPrefix + "graph.dot");
//        auto& p = *program;

        usleep(100000);
        program.accept(visitor);
        usleep(100000);
        visitor->finish();
    }
    fb.close();
//        program = Grammar::ParseCin();
    return 0;
}