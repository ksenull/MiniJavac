#include <iostream>
#include <fstream>

#include "tree/Statements.h"
#include "../ast/nodes/Nodes.h"
#include "../grammar/parse.h"
#include "../common/Exception.h"

#include "Translate.h"
#include "tree/PrintVisitor.h"
#include "canonize/Linearize.h"
#include "canonize/TraceSchedule.h"

static const std::string PathPrefix = "C:/Users/Kseniia/CLionProjects/minijavac_17/";

int main() {
    std::filebuf fb;
    if (fb.open (PathPrefix + "Samples/Factorial.java",std::ios::in)) {
        std::istream in(&fb);
        auto program = Grammar::Parse(in);
//        auto program = Grammar::ParseCin();
        symboltable::Table table;
        try {
            table.BuildFromAst(&program);
        }
        catch (common::MiniJavacException& e) {
            std::cerr << e.msg << std::endl;
        }

        ir::translate::CTranslator translator(&table);
        translator.AddCode(program.mainClass);
        for (auto* classNode : program.classDeclarationList->nodes) {
            auto* classDeclaration = dynamic_cast<ast::nodes::ClassDeclaration*>(classNode);
            for (auto* methodNode : classDeclaration->methods->nodes) {
                auto* methodDeclaration = dynamic_cast<ast::nodes::MethodDeclaration*>(methodNode);
                translator.AddCode(classDeclaration, methodDeclaration);
            }
        }
        ir::tree::PrintVisitor visitor(PathPrefix + "ir/graph.dot");
//        translator.GetRoot()->GetNext()->GetBody()->accept(&visitor);

        ir::tree::CNaiveJumpBlockScheduler scheduler;
        ir::translate::CCodeFragment* cur = translator.GetRoot()->GetNext();
//        while (cur) {
            auto stms = ir::tree::Linearize(cur->GetBody());
            stms = scheduler.schedule(stms);
            for (auto* stm : stms.nodes) {
                if (stm != nullptr)
                    stm->accept(&visitor);
            }
            cur = cur->GetNext();
//        }
        visitor.finish();
    }

    return 0;
}