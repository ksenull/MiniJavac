project(AST)

add_subdirectory(drawgraph)

set(NODES_CLASSES
        nodes/Node.h
        nodes/Nodes.h
        nodes/Identifier.cpp
        nodes/ArgumentDeclaration.cpp
        nodes/ClassDeclaration.cpp
        nodes/Expression.cpp
        nodes/MainClass.cpp
        nodes/MethodDeclaration.cpp
        nodes/Program.cpp
        nodes/Statement.cpp
        nodes/Type.cpp
        nodes/VariableDeclaration.cpp)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(VISUALIZERS PrintVisitor.cpp)
set(SOURCE_FILES main.cpp ${NODES_CLASSES} ${PARSE} ${VISUALIZERS})

add_executable(AST ${SOURCE_FILES})

target_link_libraries(AST)
set_property(TARGET AST PROPERTY CXX_STANDARD 14)
