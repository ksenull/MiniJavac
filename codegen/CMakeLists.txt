project(codegen)

set(PARSE ../grammar/Scanner.cpp ../grammar/Parser.cpp ../grammar/parse.cpp)
set(SYMBOLTABLE ../symboltable/Table.cpp
        ../symboltable/Symbol.cpp
        ../symboltable/ClassInfo.cpp
        ../symboltable/MethodInfo.cpp
        ../symboltable/VariableInfo.cpp
        ../symboltable/TypeCheckVisitor.cpp)
set(FRAME ../ir/X86TypeSpec.cpp ../ir/Frame.cpp)
set(TRANSLATE
        ../ir/translate/TranslateVisitor.cpp
        ../ir/translate/NodeConverter.cpp
        ../ir/Translate.cpp
        ../ir/translate/CodeFragment.h )
set(TREE ../ir/tree/Expressions.h ../ir/tree/Statements.h ../ir/tree/IVisitor.h ../ir/Temp.cpp)
set(CANON ../ir/canonize/Reorder.cpp ../ir/canonize/Linearize.cpp ../ir/canonize/TraceSchedule.cpp)
set(FASM fasm/FASMCodegen.h fasm/FASMCodegen.cpp fasm/FASMInstruction.h fasm/FASMInstruction.cpp fasm/FASMOperand.h fasm/FASMOperand.cpp)
set(CODEGEN Codegen.h Instruction.h Codegen.cpp ${FASM})
set(SOURCE_FILES main.cpp ${PARSE} ${SYMBOLTABLE} ${ACCESS} ${FRAME} ${TREE} ${TRANSLATE} ${AST} ${CANON} ${CODEGEN})

add_executable(CODEGEN ${SOURCE_FILES})

target_link_libraries(CODEGEN)
set_property(TARGET CODEGEN PROPERTY CXX_STANDARD 14)
