cmake_minimum_required(VERSION 3.9)
project(AST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Nodes/Identifier.h Nodes/Expressions/PlusExp.h IVisitor.cpp main.cpp Nodes/Expressions/MinusExp.h Nodes/Expressions/MultExp.h Nodes/Expressions/AndExp.h Nodes/Expressions/LessExp.h Nodes/Expressions/GetItemExp.h Nodes/Expressions/LengthExp.h Nodes/Expressions/MethodCall.h Nodes/Expressions/IntegerExp.h Nodes/Expressions/BoolExp.h Nodes/Expressions/IdentifierExp.h Nodes/Expressions/ThisExp.h Nodes/Expressions/NewIntExpression.h Nodes/Expressions/NewExp.h Nodes/Expressions/NotExp.h Nodes/IStatement.h Nodes/Statements/BlockStat.h Nodes/Statements/IfStat.h Nodes/Statements/WhileStat.h Nodes/Statements/PrintStat.h Nodes/Statements/AssignStat.h Nodes/Type.h Nodes/Types/ArrayOfInt.h Nodes/Types/Boolean.h Nodes/Types/Int.h Nodes/Types/CustomClass.h)

add_executable(AST ${SOURCE_FILES})