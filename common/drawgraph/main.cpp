#include <iostream>
#include <fstream>

#include "GraphV.h"

static const std::string PathPrefix = "/home/ksenull/workspace/test/minijavac_17/";

int main() {
    ast::visualize::Graph graph{};
    graph.readFromFile(PathPrefix + "ir/graph.dot");
    graph.savePng(PathPrefix + "common/drawgraph/graph.png");
    graph.release();
    return 0;
}