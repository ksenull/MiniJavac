#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
    }
//        program = Grammar::ParseCin();
    return 0;
}