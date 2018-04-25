#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "ModuleTable.h"
#include "../common/Exception.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

using namespace symboltable;

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
        ModuleTable moduleTable;
        try {
            moduleTable.BuildFromAst(program);
        }
        catch (common::MiniJavacException& e) {
            std::cerr << e.msg << std::endl;
        }
    }
//        program = Grammar::ParseCin();
    return 0;
}