project(SymbolTable)

set(HEADER_FILES Symbol.h)
set(SOURCE_FILES main.cpp)

add_executable(SymbolTable ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(SymbolTable)
set_property(TARGET SymbolTable PROPERTY CXX_STANDARD 14)
