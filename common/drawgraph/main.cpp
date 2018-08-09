#include <iostream>
#include <fstream>

#include "GraphV.h"

static const std::string PathPrefix = "C:/Users/Kseniia/CLionProjects/minijavac_17/ast/";

int main() {
    ast::visualize::Graph graph{};
    graph.readFromFile(PathPrefix + "graph.dot");
    graph.savePng(PathPrefix + "graph.png");
    graph.release();
    return 0;
}