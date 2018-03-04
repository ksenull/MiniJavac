#pragma once

#include "Node.h"

namespace ast {
    namespace nodes {
        class MainClass : Node {
        public:
            void accept(IVisitor* visitor);
        };
    }
}
