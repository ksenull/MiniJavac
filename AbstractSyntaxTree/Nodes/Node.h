//
// Created by kitnoel on 03.12.17.
//

#ifndef MINIJAVAC_NODE_H
#define MINIJAVAC_NODE_H

class Node {
public:
    virtual void Accept(IVisitor&) const = 0;
};

#endif //MINIJAVAC_NODE_H
