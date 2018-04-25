#pragma once

#include <list>
#include <unordered_map>

#include "Symbol.h"
#include "../ast/nodes/INode.h"

namespace symboltable {

    class Table { // for symbols in single class
    public:
        using Block = std::unordered_map<Symbol*, IInfo*>;

        void BuildFromAst(ast::nodes::INode* node);

        void AddBlock(ast::nodes::INode*);

        void RemoveBlock();
        
    private:
        std::list<Block> blocks;
    };
}