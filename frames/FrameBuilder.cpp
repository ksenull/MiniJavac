//
// Created by ksenull on 4/30/18.
//
#include "FrameBuilder.h"

#include "X86MiniJavaFrame.h"

namespace frames {
    using TypeInfo = ST::TypeInfo;

    IFrame* FrameBuilder::BuildFromMain(ast::nodes::MainClass* mainClass) {
        IFrame* frame = new CX86MiniJavaFrame();

        auto* classSymbol = ST::getIntern(mainClass->name.name);
        TypeInfo callerType(ST::VT_Object, classSymbol);

        frame->AddFormal(callerType);

        // TODO add main locals
    }

    IFrame* FrameBuilder::BuildFromST(ST::Symbol* classSymbol, ST::Symbol* methodSymbol) {
        IFrame* frame = new CX86MiniJavaFrame(); // TODO make template

        ST::TypeInfo callerInfo(ST::VT_Object, classSymbol);
        frame->AddFormal(callerInfo);

        auto* classInfo = table->getClassInfo(classSymbol);
        auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

        auto args = methodInfo->getArgsList();
        for (auto&& arg : args) {
            frame->AddFormal(arg.second->getType());
        }
        auto locals = methodInfo->getLocalVarsList();
        for(auto&& loc : locals) {
            frame->AddLocal(loc.second->getType());
        }
        frame->AddReturnAddress();
        frame->AddReturnType(methodInfo->getReturnType());
        return frame;
    }
}
