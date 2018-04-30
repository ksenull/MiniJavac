//
// Created by ksenull on 4/30/18.
//
#include "FrameBuilder.h"

#include "X86MiniJavaFrame.h"

namespace frames {
    using TypeInfo = ST::TypeInfo;

    IFrame* FrameBuilder::BuildFromMain(ast::nodes::MainClass* mainClass) {
        IFrame* frame = new CX86MiniJavaFrame(new X86MiniJavaTypeSpec(), 0, 0);

        auto* classSymbol = ST::getIntern(mainClass->name.name);
        TypeInfo callerType(ST::VT_Object, classSymbol);
        ST::VariableInfo varInfo(mainClass->loc, callerType);
        frame->AddFormal(classSymbol, varInfo);

        // TODO add main locals
        return frame;
    }

    IFrame* FrameBuilder::BuildFromST(Symbol* caller, ST::Symbol* classSymbol, ST::Symbol* methodSymbol) {
        IFrame* frame = new CX86MiniJavaFrame(new X86MiniJavaTypeSpec(), 0, 0); // TODO make template

        auto* classInfo = table->getClassInfo(classSymbol);

        ST::TypeInfo callerType(ST::VT_Object, classSymbol);
        ST::VariableInfo callerInfo(classInfo->loc, callerType);
        frame->AddFormal(caller, callerInfo);

        auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

        auto args = methodInfo->getArgsList();
        for (auto&& arg : args) {
            frame->AddFormal(arg.first, *arg.second);
        }
        auto locals = methodInfo->getLocalVarsList();
        for(auto&& loc : locals) {
            frame->AddLocal(loc.first, *loc.second);
        }
        frame->AddReturnAddress();
        frame->AddReturnType(methodInfo->getReturnType());
        return frame;
    }
}
