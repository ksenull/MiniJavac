#pragma once

#include "../Frame.h"
#include "../../symboltable/Table.h"
namespace ir {
    namespace AN = ast::nodes;
    namespace ST = symboltable;

    class FrameBuilder {
    public:
        FrameBuilder(ST::Table* table) : table(table) {}

        IFrame* BuildFromST(ST::Symbol* callerClass, ST::Symbol* classSymbol, ST::Symbol* methodSymbol);
        IFrame* BuildFromMain(AN::MainClass* mainClass);
    private:
        ST::Table* table;
    };
}