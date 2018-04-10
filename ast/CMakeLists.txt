project(AST)

#include_directories(nodes)

set(NODES_CLASSES
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
set(VISUALIZERS GraphV.cpp PrintVisitor.cpp)
set(SOURCE_FILES main.cpp ${NODES_CLASSES} ${PARSE} ${VISUALIZERS})

find_package(PkgConfig)
pkg_check_modules(GVC libgvc)

add_executable(AST ${SOURCE_FILES})

target_compile_options(AST PUBLIC ${GVC_CFLAGS})
target_link_libraries(AST ${GVC_LDFLAGS})
target_link_libraries(AST)
set_property(TARGET AST PROPERTY CXX_STANDARD 14)
