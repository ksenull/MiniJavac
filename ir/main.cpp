#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "../symboltable/Table.h"
#include "../common/Exception.h"
#include "TranslateVisitor.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

using namespace symboltable;
using namespace ir;

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
//        auto program = Grammar::ParseCin();
        Table table;
        try {
            table.BuildFromAst(program);
        }
        catch (common::MiniJavacException& e) {
            std::cerr << e.msg << std::endl;
        }
        translate::IRTranslateVisitor visitor;
        program.accept(&visitor);
    }

    return 0;
}