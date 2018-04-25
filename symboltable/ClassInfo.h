#pragma once

#include "MethodInfo.h"
#include "../ast/nodes/Nodes.h"

#include <list>
#include <unordered_map>

namespace symboltable {
    class ClassInfo : public IInfo {
    public:
        using Block = std::unordered_map<Symbol*, IInfo*>;

        ClassInfo(ast::nodes::MainClass*);
        ClassInfo(ast::nodes::INode*);

    private:
        std::list<Block> scopeBlocks;
    };
}