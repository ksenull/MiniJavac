project(frames)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SYMBOLTABLE  ../symboltable/Table.h ../symboltable/Table.cpp ../symboltable/Symbol.h ../symboltable/Symbol.cpp)
set(ACCESS Access.h Temp.h Temp.cpp)
set(FRAME IFrame.h X86MiniJavaFrame.h FrameBuilder.h FrameBuilder.cpp)
set(SOURCE_FILES main.cpp ${PARSE} ${SYMBOLTABLE} ${ACCESS} ${FRAME})

add_executable(FRAMES ${SOURCE_FILES})

target_link_libraries(FRAMES)
set_property(TARGET FRAMES PROPERTY CXX_STANDARD 14)
