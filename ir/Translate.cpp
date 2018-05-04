//
// Created by ksenull on 5/2/18.
//
#include "Translate.h"
#include "IFrame.h"
#include "translate/NodeConverter.h"
#include "../ast/nodes/Nodes.h"

namespace ir {
    namespace translate {

        namespace AST = ast::nodes;
        namespace IRT = tree;
        using namespace symboltable;

        tree::IStatement* translate::Translator::getIRT(AST::ClassDeclaration* classDeclaration,
                                                       AST::MethodDeclaration* methodDeclaration) {
            auto* classSymbol = getIntern(classDeclaration->id->name);
            auto* methodSymbol = getIntern(methodDeclaration->id->name);

            auto* classInfo = table->getClassInfo(classSymbol);
            auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

            auto* frame = new Frame(table, classInfo, methodInfo);

            IRTranslateVisitor visitor(table, classSymbol, frame);
            return methodDeclaration->accept(&visitor)->ToStm();
        }
    }
}
