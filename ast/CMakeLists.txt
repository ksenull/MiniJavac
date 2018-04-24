project(AST)

add_subdirectory(drawgraph)

set(NODES_CLASSES
        nodes/INode.h
        nodes/Nodes.h
        )

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(VISUALIZERS PrintVisitor.cpp)
set(SOURCE_FILES main.cpp ${NODES_CLASSES} ${PARSE} ${VISUALIZERS})

add_executable(AST ${SOURCE_FILES})

target_link_libraries(AST)
set_property(TARGET AST PROPERTY CXX_STANDARD 14)
