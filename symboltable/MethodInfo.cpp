//
// Created by ksenull on 4/25/18.
//
#include "MethodInfo.h"
#include "SymbolException.h"

namespace symboltable {

#define ADD_VARINFO_OR_THROW(var)\
    auto* symbol = getIntern(var->id.name);\
    auto search = vars.find(symbol);\
    if (search != vars.end()) {\
        throw VariableAlreadyDefinedError(symbol, search->second->loc, var->loc);\
    }\
    VariableInfo variableInfo(var->loc);\
    variableInfo.BuildFromAst(var);

    void MethodInfo::BuildFromAst(ast::nodes::MethodDeclaration* methodDeclaration) {
        for (auto* node : methodDeclaration->args->nodes) {
            if (auto* arg = dynamic_cast<ast::nodes::VariableDeclaration*>(node)) {
                ADD_VARINFO_OR_THROW(arg)
            }
        }

        for (auto* node : methodDeclaration->statementList->nodes) { // there are no nested namespaces
            if (auto* varStm = dynamic_cast<ast::nodes::VariableDeclarationStatement*>(node)) {
                auto* var = varStm->var;
                ADD_VARINFO_OR_THROW(var)
            }
        }

        returnType = methodDeclaration->returnType;
    }
}
