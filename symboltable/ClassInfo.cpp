//
// Created by ksenull on 4/25/18.
//
#include "ClassInfo.h"
#include "SymbolException.h"

namespace symboltable {
    void ClassInfo::BuildFromAst(ast::nodes::MainClass* mainClass) {
        // TODO args name and idDeclarations in main method
    }

    void ClassInfo::BuildFromAst(ast::nodes::ClassDeclaration* node) {
        if (node->base.name.empty()) {
            base = nullptr;
        } else {
            auto* symbol = getIntern(node->base.name);
            base = symbol;
        }
        for (auto* n : node->localVars->nodes) {
            if (auto* varStm = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(n)) {
                auto* var = varStm->var;
                auto* symbol = getIntern(var->id.name);
                auto search = vars.find(symbol);
                if (search != vars.end()) {
                    throw VariableAlreadyDefinedError(symbol, search->second->loc, var->loc);
                }

                VariableInfo* variableInfo = new VariableInfo(var->loc);
                variableInfo->BuildFromAst(var);

                vars.emplace(std::make_pair(symbol, variableInfo));
            }
        }

        for (auto* n : node->methods->nodes) {
            if (auto* method = dynamic_cast<ast::nodes::MethodDeclaration*>(n)) {
                auto* symbol = getIntern(method->id.name);
                auto search = methods.find(symbol); // overloads aren't supported
                if (search != methods.end()) {
                    throw MethodAlreadyDefinedError(symbol, search->second->loc, method->loc);
                }

                MethodInfo* methodInfo = new MethodInfo(method->loc);
                methodInfo->BuildFromAst(method);

                methods.emplace(std::make_pair(symbol, methodInfo));
            }
        }

    }

    Symbol* ClassInfo::getBase() const {
        return base;
    }

    ClassInfo::~ClassInfo() {
        for (auto&& var : vars) {
            delete var.second;
        }
        for (auto&& method : methods) {
            delete method.second;
        }
    }
}
