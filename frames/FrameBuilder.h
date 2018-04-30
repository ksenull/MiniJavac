#pragma once

#include "IFrame.h"
#include "../symboltable/Table.h"
namespace frames {
    namespace AN = ast::nodes;
    namespace ST = symboltable;

    class FrameBuilder {
    public:
        FrameBuilder(ST::Table* table) : table(table) {}

        IFrame* BuildFromST(ST::Symbol* classSymbol, ST::Symbol* methodSymbol);
        IFrame* BuildFromMain(AN::MainClass* mainClass);
    private:
        ST::Table* table;
    };
}