#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "Table.h"
#include "TypeCheckVisitor.h"
#include "../common/Exception.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

using namespace symboltable;

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
//        auto program = Grammar::ParseCin();
        Table table;
        try {
            table.BuildFromAst(program);
            TypeCheckVisitor visitor(table);
            program.accept(&visitor);
        }
        catch (common::MiniJavacException& e) {
            std::cerr << e.msg << std::endl;
        }
    }

    return 0;
}