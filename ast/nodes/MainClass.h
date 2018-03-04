#pragma once

#include "Node.h"
#include "Statement.h"

namespace ast {
    namespace nodes {
        class MainClass : Node {
            Identifier className;
            Identifier argsName;
            Statement st;
        public:
            MainClass(const Identifier& id1, const Identifier& id2, const Statement& _st);
            void accept(IVisitor* visitor) const;
        };
    }
}
