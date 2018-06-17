project(frames)

#add_subdirectory(X86)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SYMBOLTABLE  ../symboltable/Table.h ../symboltable/Table.cpp
        ../symboltable/Symbol.h ../symboltable/Symbol.cpp
        ../symboltable/ClassInfo.h ../symboltable/ClassInfo.cpp
        ../symboltable/MethodInfo.h ../symboltable/MethodInfo.cpp
        ../symboltable/VariableInfo.h ../symboltable/VariableInfo.cpp
        ../symboltable/TypeCheckVisitor.h ../symboltable/TypeCheckVisitor.cpp)
set(ACCESS Access.h Temp.h)
set(FRAME Frame.h ITypeSpec.h X86TypeSpec.cpp Frame.cpp)
set(TREE tree/Expressions.h tree/Statements.h tree/IVisitor.h tree/PrintVisitor.h tree/PrintVisitor.cpp)
set(TRANSLATE
        translate/TranslateVisitor.h
        translate/TranslateVisitor.cpp
        translate/NodeConverter.h
        translate/NodeConverter.cpp
        Translate.h
        Translate.cpp
        translate/CodeFragment.h)
set(AST ../ast/nodes/INode.h ../ast/nodes/Nodes.h ../ast/IVisitor.h)
set(CANON canonize/Reorder.cpp canonize/Reorder.h
        canonize/Linearize.cpp canonize/Linearize.h
        #canonize/FunctionalVisitor.h canonize/FunctionalVisitor.cpp canonize/BlocksPermutator.h
        canonize/TraceSchedule.cpp)
set(SOURCE_FILES main.cpp ${PARSE} ${SYMBOLTABLE} ${ACCESS} ${FRAME} ${TREE} ${TRANSLATE} ${AST} ${CANON} Temp.cpp)

add_executable(IR ${SOURCE_FILES})

target_link_libraries(IR)
set_property(TARGET IR PROPERTY CXX_STANDARD 14)
