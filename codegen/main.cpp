//
// Created by Kseniia on 17.06.2018.
//
#include <iostream>
#include <fstream>
#include "../grammar/parse.h"
#include "../ast/nodes/Nodes.h"
#include "../common/Exception.h"
#include "../ir/Translate.h"
#include "../ir/canonize/Linearize.h"
#include "../ir/canonize/TraceSchedule.h"

#include "fasm/FASMCodegen.h"

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

        auto codegen = codegen::fasm::CCodegen{};
        std::cout << std::endl << "--------------------------" << std::endl;

        ir::tree::CNaiveJumpBlockScheduler scheduler;
        ir::translate::CCodeFragment* cur = translator.GetRoot();
        while (cur) {
            auto stms = ir::tree::Linearize(cur->GetBody());
            stms = scheduler.schedule(stms);
//            std::cout << stms.nodes.size() << std::endl;

            auto instructions = codegen.Gen(cur->GetFrame(), stms);
            for (const auto& instr : instructions) {
                std::cout << instr.str() << std::endl;
            }

            cur = cur->GetNext();
        }

    }
    fb.close();
    return 0;
}