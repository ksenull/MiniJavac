project(x86)

set(PARSE ../../grammar/Scanner.cpp ../../grammar/Parser.cpp ../../grammar/parse.cpp)
set(SYMBOLTABLE  ../../symboltable/Table.h ../../symboltable/Table.cpp
        ../../symboltable/Symbol.h ../../symboltable/Symbol.cpp
        ../../symboltable/ClassInfo.h ../../symboltable/ClassInfo.cpp
        ../../symboltable/MethodInfo.h ../../symboltable/MethodInfo.cpp
        ../../symboltable/VariableInfo.h ../../symboltable/VariableInfo.cpp)
set(ACCESS ../Access.h ../Temp.h)
set(FRAME ../Frame.h X86MiniJavaFrame.h FrameBuilder.h FrameBuilder.cpp X86MiniJavaFrame.cpp ../ITypeSpec.h X86TypeSpec.h ../X86TypeSpec.cpp)
set(SOURCE_FILES main.cpp ${PARSE} ${SYMBOLTABLE} ${ACCESS} ${FRAME})

add_executable(X86 ${SOURCE_FILES})

target_link_libraries(X86)
set_property(TARGET X86 PROPERTY CXX_STANDARD 14)
