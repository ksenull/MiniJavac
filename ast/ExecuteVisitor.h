#pragma once

#include "IVisitor.h"

namespace ast {

    template <typename T>
    class ExecuteVisitor : public IVisitor<T> {
    };

}

