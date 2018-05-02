#pragma once

#include "translate/TranslateVisitor.h"

namespace ir {
    namespace translate {

        class Translator {
        public:
            explicit Translator(symboltable::Table* table) : table(table) {}

            tree::IStatement* getIRT(ast::nodes::ClassDeclaration* classDeclaration, ast::nodes::MethodDeclaration* methodDeclaration);

        private:
            symboltable::Table* table;
        };
    }
}