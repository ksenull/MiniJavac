#pragma once

#include "translate/TranslateVisitor.h"

namespace ir {
    namespace translate {

        class Translator {
        public:
            explicit Translator(symboltable::Table* table) : table(table) {}

            ISubtreeWrapper* getIRT(ast::nodes::ClassDeclaration* classDeclaration, ast::nodes::MethodDeclaration* methodDeclaration);

        private:
            symboltable::Table* table;
            IFrame* frame;
            ast::nodes::ClassDeclaration* classDeclaration;
            ast::nodes::MethodDeclaration* methodDeclaration;
        };
    }
}