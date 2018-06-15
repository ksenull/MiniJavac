#pragma once

#include "translate/TranslateVisitor.h"
#include "translate/CodeFragment.h"

namespace ir {
    namespace translate {

        class CTranslator {
        public:
            explicit CTranslator(symboltable::Table* table) : table(table), root(nullptr), current(nullptr) {}

//            void AddCode(ast::nodes::MainClass* mainClass);

            void AddCode(ast::nodes::ClassDeclaration* classDeclaration, ast::nodes::MethodDeclaration* methodDeclaration);

            void AddCode(ast::nodes::MainClass *mainClass);

            tree::IStatement* GetRootIRT() {
                return root->GetBody();
            }
        private:
            symboltable::Table* table;
            CCodeFragment* root;
            CCodeFragment* current;


        };
    }
}