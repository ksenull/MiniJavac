//
// Created by ksenull on 5/2/18.
//
#include "Translate.h"

namespace ir {
    namespace translate {

        namespace AST = ast::nodes;
        namespace IRT = tree;
        using namespace symboltable;

        ISubtreeWrapper* translate::Translator::getIRT(AST::ClassDeclaration* classDeclaration,
                                                       AST::MethodDeclaration* methodDeclaration) {
            auto* classSymbol = getIntern(classDeclaration->id.name);
            auto* methodSymbol = getIntern(methodDeclaration->id.name);

            auto* classInfo = table->getClassInfo(classSymbol);
            auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

            auto* frame = new Frame(table, classInfo, methodInfo);

            IRTranslateVisitor visitor(frame);
            return methodDeclaration->accept(&visitor);
        }
    }
}
