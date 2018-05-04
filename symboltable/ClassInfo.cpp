//
// Created by ksenull on 4/25/18.
//
#include "ClassInfo.h"
#include "SymbolException.h"

namespace symboltable {
    void ClassInfo::BuildFromAst(ast::nodes::MainClass* mainClass) {
        base = nullptr;
        if (auto* nested = dynamic_cast<ast::nodes::NestedStatement*>(mainClass->st)) {
            for (auto* st : nested->statementList->nodes) {
                if (auto* varDecl = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(st)) {
                    VariableInfo* variableInfo = new VariableInfo(varDecl->var->getLoc());
                    variableInfo->BuildFromAst(varDecl->var);

                    auto* symbol = getIntern(varDecl->var->id->name);
                    vars.emplace(std::make_pair(symbol, variableInfo));
                }
            }
        }
        // TODO

        MethodInfo* methodInfo = new MethodInfo(mainClass->getLoc());
        methodInfo->BuildFromAst(mainClass);
        auto* symbol = getIntern("main");
        methods.emplace(std::make_pair(symbol, methodInfo));


    }

    void ClassInfo::BuildFromAst(ast::nodes::ClassDeclaration* node) {
        if (node->base) {
            auto* symbol = getIntern(node->base->name);
            base = symbol;
        } else {
            base = nullptr;
        }
        for (auto* n : node->localVars->nodes) {
            if (auto* varStm = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(n)) {
                auto* var = varStm->var;
                auto* symbol = getIntern(var->id->name);
                auto search = vars.find(symbol);
                if (search != vars.end()) {
                    throw VariableAlreadyDefinedError(symbol, search->second->getLoc(), var->getLoc());
                }

                VariableInfo* variableInfo = new VariableInfo(var->getLoc());
                variableInfo->BuildFromAst(var);

                vars.emplace(std::make_pair(symbol, variableInfo));
            }
        }

        for (auto* n : node->methods->nodes) {
            if (auto* method = dynamic_cast<ast::nodes::MethodDeclaration*>(n)) {
                auto* symbol = getIntern(method->id->name);
                auto search = methods.find(symbol); // overloads aren't supported
                if (search != methods.end()) {
                    throw MethodAlreadyDefinedError(symbol, search->second->getLoc(), method->getLoc());
                }

                MethodInfo* methodInfo = new MethodInfo(method->getLoc());
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

    MethodInfo* ClassInfo::getMethodInfo(Symbol* methodName) const {
        auto&& search = methods.find(methodName);
        return (search == methods.end()) ? nullptr : search->second;
    }

    std::unordered_map<Symbol*, VariableInfo*> ClassInfo::getVars() const {
        return vars;
    }

    std::unordered_map<Symbol*, MethodInfo*> ClassInfo::getMethods() const {
        return methods;
    }

    VariableInfo* ClassInfo::getVariableInfo(Symbol* varSymbol) const {
        auto&& search = vars.find(varSymbol);
        return (search == vars.end()) ? nullptr : search->second;
    }

}
