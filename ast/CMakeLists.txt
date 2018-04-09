project(AST)

#include_directories(nodes)

set(NODES_CLASSES
        nodes/ArgumentDeclaration.cpp
        nodes/ClassDeclaration.cpp
        nodes/Expression.cpp
        nodes/Identifier.cpp
        nodes/MainClass.cpp
        nodes/MethodDeclaration.cpp
        nodes/Program.cpp
        nodes/Statement.cpp
        nodes/Type.cpp
        nodes/VariableDeclaration.cpp)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SOURCE_FILES PrintVisitor.cpp main.cpp ${NODES_CLASSES} ${PARSE})
add_executable(AST ${SOURCE_FILES})

target_link_libraries(AST)
set_property(TARGET AST PROPERTY CXX_STANDARD 14)
