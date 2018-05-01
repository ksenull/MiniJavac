project(frames)

add_subdirectory(X86)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SYMBOLTABLE  ../symboltable/Table.h ../symboltable/Table.cpp
        ../symboltable/Symbol.h ../symboltable/Symbol.cpp
        ../symboltable/ClassInfo.h ../symboltable/ClassInfo.cpp
        ../symboltable/MethodInfo.h ../symboltable/MethodInfo.cpp
        ../symboltable/VariableInfo.h ../symboltable/VariableInfo.cpp
        ../symboltable/TypeCheckVisitor.h ../symboltable/TypeCheckVisitor.cpp)
set(ACCESS Access.h Temp.h)
set(FRAME IFrame.h ITypeSpec.h)
set(TREE Expressions.h Statements.h)
set(TRANSLATE TranslateVisitor.h TranslateVisitor.cpp NodeConverter.h NodeConverter.cpp)
set(SOURCE_FILES main.cpp ${PARSE} ${SYMBOLTABLE} ${ACCESS} ${FRAME} ${TREE} ${TRANSLATE})

add_executable(IR ${SOURCE_FILES})

target_link_libraries(IR)
set_property(TARGET IR PROPERTY CXX_STANDARD 14)
