#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "../symboltable/Table.h"
#include "../symboltable/TypeCheckVisitor.h"
#include "../common/Exception.h"
#include "FrameBuilder.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

using namespace symboltable;
using namespace frames;
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
        FrameBuilder frameBuilder(&table);
        auto* symbol = getIntern("Fac");
        ClassInfo* cl = table.getClassInfo(symbol);
        IFrame* frame = frameBuilder.BuildFromST(symbol, symbol, getIntern("ComputeFac"));
        frame->PrettyPrint();
    }

    return 0;
}