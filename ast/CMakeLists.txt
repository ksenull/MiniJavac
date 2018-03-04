project(AST)

include_directories(nodes)

set(NODES_CLASSES nodes/MainClass.cpp nodes/Program.cpp)
set(SOURCE_FILES PrintVisitor.cpp main.cpp ${NODES_CLASSES})
set(HEADER_FILES Identifier.h MainClass.h Node.h Program.h IVisitor.h PrintVisitor.h)
add_executable(AST ${SOURCE_FILES})

target_link_libraries(AST)
set_property(TARGET AST PROPERTY CXX_STANDARD 14)
