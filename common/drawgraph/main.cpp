#include <iostream>
#include <fstream>

#include "GraphV.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/ir/";

int main() {
    ast::visualize::Graph graph{};
    graph.readFromFile(PathPrefix + "graph.dot");
    graph.savePng(PathPrefix + "graph.png");
    graph.release();
    return 0;
}