//
// Created by ksenull on 5/2/18.
//
#include "Translate.h"
#include "Frame.h"
#include "translate/NodeConverter.h"
#include "../ast/nodes/Nodes.h"
#include "translate/CodeFragment.h"

namespace ir {
    namespace translate {

        namespace AST = ast::nodes;
        namespace IRT = tree;
        using namespace symboltable;

        void translate::CTranslator::AddCode(AST::MainClass* mainClass) {
            auto* classSymbol = getIntern(mainClass->id->name);
            auto* methodSymbol = getIntern("main");

            auto* classInfo = table->getClassInfo(classSymbol);
            auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

            auto* frame = new Frame(table, classInfo, methodInfo);

            IRTranslateVisitor visitor(table, classSymbol, frame);
            auto* body = mainClass->accept(&visitor)->ToStm();

            auto* code = new CCodeFragment(frame, body, classSymbol->name, "main");
            if (root == nullptr) {
                root = code;
                current = root;
            }
            else {
                current->SetNext(code);
                current = current->GetNext();
            }
        }

        void translate::CTranslator::AddCode(AST::ClassDeclaration* classDeclaration,
                                                       AST::MethodDeclaration* methodDeclaration) {
            auto* classSymbol = getIntern(classDeclaration->id->name);
            auto* methodSymbol = getIntern(methodDeclaration->id->name);

            auto* classInfo = table->getClassInfo(classSymbol);
            auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

            auto* frame = new Frame(table, classInfo, methodInfo);

            IRTranslateVisitor visitor(table, classSymbol, frame);
            auto* body = methodDeclaration->accept(&visitor)->ToStm();

            auto* code = new CCodeFragment(frame, body, classSymbol->name, methodSymbol->name);
            if (root == nullptr) {
                root = code;
                current = root;
            }
            else {
                current->SetNext(code);
                current = current->GetNext();
            }
        }
    }
}
