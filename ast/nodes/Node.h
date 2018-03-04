#pragma once

#include "../IVisitor.h"

namespace ast {
    namespace nodes {
        class Node  {
        public:
            virtual void accept(IVisitor* visitor) const = 0;
        };
    }
}