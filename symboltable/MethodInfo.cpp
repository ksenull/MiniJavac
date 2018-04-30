//
// Created by ksenull on 4/25/18.
//
#include "MethodInfo.h"
#include "SymbolException.h"

namespace symboltable {

#define ADD_VAR_TO_VARLIST(vars) \
    (vars).emplace_back(std::make_pair(symbol, variableInfo));

#define ADD_VARINFO_OR_THROW(var)\
    auto* symbol = getIntern((var)->id.name);\
    auto search = vars.find(symbol);\
    if (search != vars.end()) {\
        throw VariableAlreadyDefinedError(symbol, search->second->loc, (var)->loc);\
    }\
    VariableInfo* variableInfo = new VariableInfo((var)->loc);\
    variableInfo->BuildFromAst(var);\
    vars.emplace(std::make_pair(symbol, variableInfo));

    void MethodInfo::BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration) {

        for (auto* node : methodDeclaration->args->nodes) {
            if (auto* arg = dynamic_cast<ast::nodes::VariableDeclaration*>(node)) {
                ADD_VARINFO_OR_THROW(arg)
                ADD_VAR_TO_VARLIST(args)
            }
        }

        for (auto* node : methodDeclaration->statementList->nodes) { // there are no nested namespaces
            if (auto* varStm = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(node)) {
                auto* var = varStm->var;
                ADD_VARINFO_OR_THROW(var)
                ADD_VAR_TO_VARLIST(localVars)
            }
        }

        returnType = TypeInfo(methodDeclaration->returnType);
    }

    MethodInfo::ArgsList MethodInfo::getArgsList() { // TODO save and pass it efficiently
        return args;
    }

    MethodInfo::ArgsList MethodInfo::getLocalVarsList() {
        return localVars;
    }

    TypeInfo MethodInfo::getReturnType() const {
        return returnType;
    }

    VariableInfo* MethodInfo::getVariableInfo(Symbol* varSymbol) const {
        auto&& search = vars.find(varSymbol);
        return (search != vars.end()) ? search->second : nullptr;
    }
}
