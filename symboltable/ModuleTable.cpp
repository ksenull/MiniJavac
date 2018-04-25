//
// Created by ksenull on 4/25/18.
//
#include "ModuleTable.h"
#include "SymbolException.h"
//#include "../ast/nodes/Nodes.h"
namespace symboltable {
    ModuleTable::ModuleTable(const ast::nodes::Program& program) {
        auto* symbol = &program.mainClass->name;
        auto classInfo = ClassInfo(program.mainClass);
        classesTable.emplace(std::make_pair(symbol, &classInfo));
        for (auto* node : program.classDeclarationList->nodes) {
            if (auto cl = dynamic_cast<ast::nodes::ClassDeclaration*>(node)) {
                symbol = &cl->id;
                auto search = classesTable.find(symbol);
                if (search != classesTable.end()) {
                    throw DuplicateClassError(symbol, search->second->loc, cl->loc);
                }
                classInfo = ClassInfo(cl);
                classesTable.emplace(std::make_pair(&program.mainClass->name, &classInfo));
            }
        }
    }
}
