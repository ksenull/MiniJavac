#include <iostream>
#include <fstream>

#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "../common/Exception.h"
#include "Translate.h"
#include "tree/PrintVisitor.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
//        auto program = Grammar::ParseCin();
        symboltable::Table table;
        try {
            table.BuildFromAst(program);
        }
        catch (common::MiniJavacException& e) {
            std::cerr << e.msg << std::endl;
        }

        ir::translate::Translator translator(&table);
        auto* classDeclaration = dynamic_cast<ast::nodes::ClassDeclaration*>(program.classDeclarationList->nodes[0]);
        auto* methodDeclaration = dynamic_cast<ast::nodes::MethodDeclaration*>(classDeclaration->methods->nodes[0]);
        auto* irt = translator.getIRT(classDeclaration, methodDeclaration);
    }

    return 0;
}