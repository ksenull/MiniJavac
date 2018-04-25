project(SymbolTable)

set(HEADER_FILES Symbol.h VariableInfo.h MethodInfo.h ClassInfo.h Table.h ../ast/nodes/Identifier.h ../ast/nodes/Nodes.h)
set(SOURCE_FILES main.cpp Table.cpp)
set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)

add_executable(SymbolTable ${SOURCE_FILES} ${HEADER_FILES} ${PARSE})

target_link_libraries(SymbolTable)
set_property(TARGET SymbolTable PROPERTY CXX_STANDARD 14)
