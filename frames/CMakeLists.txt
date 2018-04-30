project(frames)


set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SOURCE_FILES main.cpp IFrame.h X86MiniJavaFrame.h ${PARSE})

add_executable(FRAMES ${SOURCE_FILES})

target_link_libraries(FRAMES)
set_property(TARGET FRAMES PROPERTY CXX_STANDARD 14)
