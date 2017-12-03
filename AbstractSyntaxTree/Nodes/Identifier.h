//
// Created by kitnoel on 03.12.17.
//

#ifndef AST_IDENTIFIER_H
#define AST_IDENTIFIER_H
#include <iostream>

#include "Node.h"
#include "../IVisitor.h"

class Identifier : public Node {
    std::string name;
public:
    void Accept(IVisitor& visitor) const;
};

#endif //AST_IDENTIFIER_H
