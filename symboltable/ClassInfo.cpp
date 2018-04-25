//
// Created by ksenull on 4/25/18.
//
#include "ClassInfo.h"
#include "SymbolException.h"

namespace symboltable {
    ClassInfo::ClassInfo(ast::nodes::MainClass* mainClass) : IInfo(mainClass->loc) {}

    ClassInfo::ClassInfo(ast::nodes::ClassDeclaration* node) : IInfo(node->loc) {
        if (node->base.name.empty()) {
            base = nullptr;
        } else {
            auto* symbol = getIntern(node->base.name);
        }
        for (auto* n : node->localVars->nodes) {
            if (auto* varStm = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(n)) {
                auto* var = varStm->var;
                auto* symbol = getIntern(var->id.name);
                auto search = vars.find(symbol);
                if (search != vars.end()) {
                    throw VariableAlreadyDefinedError(symbol, search->second->loc, var->loc);
                }
                VariableInfo variableInfo(var);
                vars.emplace(std::make_pair(symbol, &variableInfo));
            }
        }

        for (auto* n : node->methods->nodes) {
            if (auto* method = dynamic_cast<ast::nodes::MethodDeclaration*>(n)) {
                auto* symbol = getIntern(method->id.name);
                auto search = methods.find(symbol); // overloads aren't supported
                if (search != methods.end()) {
                    throw MethodAlreadyDefinedError(symbol, search->second->loc, method->loc);
                }
                MethodInfo methodInfo(method);
                methods.emplace(std::make_pair(symbol, &methodInfo));
            }
        }

    }
}
