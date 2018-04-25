//
// Created by ksenull on 4/25/18.
//
#include "Table.h"
#include "SymbolException.h"

namespace symboltable {

    void Table::BuildFromAst(const ast::nodes::Program& program) {
        auto* symbol = getIntern(program.mainClass->name.name);

        auto classInfo = ClassInfo(program.mainClass->loc);
        classInfo.BuildFromAst(program.mainClass);

        classesTable.emplace(std::make_pair(symbol, &classInfo));

        for (auto* node : program.classDeclarationList->nodes) {
            if (auto cl = dynamic_cast<ast::nodes::ClassDeclaration*>(node)) {
                symbol = getIntern(cl->id.name);
                auto search = classesTable.find(symbol);
                if (search != classesTable.end()) {
                    throw DuplicateClassError(symbol, search->second->loc, cl->loc);
                }

                classInfo = ClassInfo(cl->loc);
                classInfo.BuildFromAst(cl);

                classesTable.emplace(std::make_pair(symbol, &classInfo));
            }
        }

        for (auto* node : program.classDeclarationList->nodes) { // Optimize me!(
            if (auto cl = dynamic_cast<ast::nodes::ClassDeclaration*>(node)) {
                checkBase(cl);
            }
        }
    }
    void Table::checkBase(ast::nodes::ClassDeclaration* node) const {
        if (node != nullptr && !node->base.name.empty()) {
            auto* symbol = getIntern(node->base.name);
            auto search = classesTable.find(symbol);
            if (search == classesTable.end()) {
                throw CantFindSymbolError(symbol, node->loc);
            }
        }
    }
}
