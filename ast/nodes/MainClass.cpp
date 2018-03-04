//
// Created by ksenull on 3/4/18.
//

#include "MainClass.h"

namespace ast {
    namespace nodes {

        MainClass::MainClass(const Identifier& id1, const Identifier& id2, const Statement& _st) :
        className(id1), argsName(id2), st(_st){}

        void MainClass::accept(IVisitor* visitor) const {
            visitor->visit(this);
        }
    }
}