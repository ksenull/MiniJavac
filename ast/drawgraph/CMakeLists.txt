project(ASTGraph)

set(SOURCE_FILES main.cpp GraphV.cpp)

find_package(PkgConfig)
pkg_check_modules(GVC libgvc)

#add_definitions(-DSourceDir)
add_executable(ASTGraph ${SOURCE_FILES})

target_compile_options(ASTGraph PUBLIC ${GVC_CFLAGS})
target_link_libraries(ASTGraph ${GVC_LDFLAGS})
target_link_libraries(ASTGraph)
set_property(TARGET ASTGraph PROPERTY CXX_STANDARD 14)
