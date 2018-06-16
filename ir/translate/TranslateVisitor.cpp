//
// Created by ksenull on 5/1/18.
//
#include <cassert>
#include "TranslateVisitor.h"
#include "NodeConverter.h"
#include "../../common/Exception.h"
#include "../../ast/nodes/Nodes.h"

using BaseException = common::MiniJavacException;

struct CantBuildIrtError : BaseException {
    CantBuildIrtError() : BaseException("Trying to build IR tree from non-method node") {}
};

namespace ir {
    namespace translate {
        namespace IRT = tree;
        namespace AST = AN;
        namespace ST = symboltable;

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Program* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MainClass* node) const {
            auto* methodLabel = ST::getIntern(node->id->name);
            auto* methodInfo = classInfo->getMethodInfo(methodLabel);
//            assert( methodInfo->getLocalVarsList() == nullptr);

            if (node->st != nullptr) {
                auto* bodySubtree = node->st->accept(this);
                return bodySubtree;
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclaration* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclarationList* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatementList* node) const {
            auto&& nodes = node->nodes;

            if (nodes.size() == 1) {
                return nodes[0]->accept(this);
            }
            else {
                ISubtreeWrapper* curSeq = nodes[nodes.size() - 1]->accept(this);
                for (unsigned long i = nodes.size() - 2; i >= 0; i--) {
                    auto* left = nodes[i]->accept(this);
                    curSeq = new CStmConverter(new IRT::SeqStatement(left->ToStm(), curSeq->ToStm()));
                }
                return curSeq;
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatement* node) const {
            return node->var->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclaration* node) const {
            switch (node->type->tt) {
                case AN::TT_Bool:
                case AN::TT_Int:
                case AN::TT_Void:
                    // already  defined in method declaration visit
                    return nullptr;
                case AN::TT_Array:
                case AN::TT_Object:
                    // could be defined only in special statements;
                    return nullptr;
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Type* node) const {
            // type could appear only in definition, which are all perforemed in method translation
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclarationList* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclaration* node) const {
            ST::TypeInfo classType(ST::VT_Object, classSymbol);
            ST::VariableInfo thisInfo({}, classType);
            Label* label = ST::getIntern("this");
            frame->AddFormal(label, thisInfo);

            auto* methodLabel = ST::getIntern(node->id->name);
            auto* methodInfo = classInfo->getMethodInfo(methodLabel);

            for (auto&& arg : methodInfo->getArgsList()) {
                frame->AddFormal(arg.first, *arg.second); // var symbol, var info
            }

            for (auto&& local : methodInfo->getLocalVarsList()) {
                frame->AddLocal(local.first, *local.second);
            }

            if (node->statementList != nullptr && !node->statementList->nodes.empty()) {
                auto* bodySubtree = node->statementList->accept(this);

                if (node->returnExp != nullptr) {
                    auto* returnExpSubtree = node->returnExp->accept(this);

                    return new CStmConverter(new IRT::SeqStatement(bodySubtree->ToStm(), new IRT::MoveStatement(
                            frame->ReturnValue()->getExp(),
                            returnExpSubtree->ToExp())));
                }

                return bodySubtree;
            }
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentDeclarationList* node) const {
            // all arguments have already been added in method translation
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CStatementList* node) const {
            auto&& nodes = node->nodes;

            if (nodes.size() == 1) {
                return nodes[0]->accept(this);
            }
            else {
                ISubtreeWrapper* curSeq = nodes[nodes.size() - 1]->accept(this);
                for (long i = nodes.size() - 2; i >= 0; i--) {
                    auto* left = nodes[i]->accept(this);
                    if (auto* ifStm = dynamic_cast<AST::IfStatement*>(nodes[i])) {
                        Label* done = ST::getIntern("done");
                        curSeq = new CStmConverter(new IRT::SeqStatement(left->ToStm(), curSeq->ToStm()));
                    }
                    else if (auto* whileStm = dynamic_cast<AST::WhileStatement*>(nodes[i])) {
                        Label* done = ST::getIntern("done");
                        curSeq = new CStmConverter(new IRT::SeqStatement(left->ToStm(), curSeq->ToStm()));
                    }
                    else if (auto* varDeclStm = dynamic_cast<AST::VariableDeclarationStatement*>(nodes[i])) {
                        continue;  // all local variables were alredy added to frame in MethodDeclaration;
                    }
                    else {
                        curSeq = new CStmConverter(new IRT::SeqStatement(left->ToStm(), curSeq->ToStm()));
                    }
                }
                return curSeq;
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NestedStatement* node) const {
            return node->statementList->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IfStatement* node) const {
            auto* cond = node->condition->accept(this);
            Label* ifTrue = ST::getIntern("ifTrue");
            Label* ifFalse = ST::getIntern("ifFalse");
            Label* done = ST::getIntern("done");

            auto* ifTrueStm = new IRT::SeqStatement(node->ifStatement->accept(this)->ToStm(), new IRT::JumpStatement(*done));
            auto* ifFalseStm = node->elseStatement->accept(this)->ToStm();
            auto* right = new IRT::SeqStatement(
                    new IRT::SeqStatement(
                            new IRT::LabelStatement(*ifTrue),
                            ifTrueStm
                    ), new IRT::SeqStatement(
                            new IRT::LabelStatement(*ifFalse),
                            ifFalseStm
                    ));
            auto* left = cond->ToConditional(*ifTrue, *ifFalse);
            return new CStmConverter(new IRT::SeqStatement(left, right));

        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::WhileStatement* node) const {
            auto* loopLabel = ST::getIntern("loop");
            auto* bodyLabel = ST::getIntern("body");
            auto* doneLabel = ST::getIntern("done");
            auto* loopPartStm = new IRT::SeqStatement(
                new IRT::LabelStatement(*loopLabel),
                node->condition->accept(this)->ToConditional(*doneLabel, *bodyLabel)
            );
            auto* bodyPartStm = new IRT::SeqStatement(
                    new IRT::LabelStatement(*bodyLabel),
                    node->statement->accept(this)->ToStm()
            );
            return new CStmConverter(new IRT::SeqStatement(loopPartStm, bodyPartStm));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::PrintStatement* node) const {
            auto* label = ST::getIntern("Print");
            auto* args = new IRT::CExpressionList();
            auto* arg = node->exp->accept(this)->ToExp();
            args->nodes.emplace_back(arg);
            return new CExpConverter(new IRT::CallExpression(label, args));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::AssignStatement* node) const {
            auto* source = node->exp->accept(this);
            auto* target = AST::IdExpression(node->id, {}).accept(this);
            return new CStmConverter(new IRT::MoveStatement(target->ToExp(), source->ToExp()));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayAssignStatement* node) const {
            auto* source  = node->id->accept(this);
            auto* index = node->arrExp->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentsList* node) const {
            //arguments should be processed in CallStm
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BinopExpression* node) const {
            auto* left = node->left->accept(this)->ToExp();
            auto* right = node->right->accept(this)->ToExp();
            IRT::BinaryOperation op;
            switch (node->type) {
                case AST::BOT_Plus:
                    op = IRT::BO_Plus;
                    break;
                case AST::BOT_Minus:
                    op = IRT::BO_Minus;
                    break;
                case AST::BOT_Multiply:
                    op = IRT::BO_Mul;
                    break;
                case AST::BOT_And:
                    op = IRT::BO_And;
                    break;
                default:
                    return new CCondStmConverter((node->type == AST::BOT_Equal) ? IRT::RO_Eq : IRT::RO_Lt,
                                             left, right);
            }
            return new CExpConverter(new IRT::BinopExpression(left, op, right));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayItemExpression* node) const {
            auto* arrSubtree = node->arr->accept(this);  // content of array id is an address to its memory, so we still need to obtain its value
            auto* indexSubtree = node->ind->accept(this);
            auto* offset = new IRT::BinopExpression(indexSubtree->ToExp(), IRT::BO_Mul, new IRT::ConstExpression(frame->GetWordSize()));
            auto* offsetOfArrayBegin = new IRT::BinopExpression(new IRT::ConstExpression(frame->GetWordSize()), IRT::BO_Plus, offset);
            auto* addr = new IRT::BinopExpression(arrSubtree->ToExp(), IRT::BO_Plus, offsetOfArrayBegin);
            return new CExpConverter(new IRT::MemExpression(addr));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayLengthExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CallExpression* node) const {
            auto* obj = node->obj->accept(this);

            auto* args = new IRT::CExpressionList();
            args->nodes.emplace_back(obj->ToExp());
            for (auto* arg : node->args->nodes) {
                args->nodes.emplace_back(arg->accept(this)->ToExp());
            }

            auto* methodLabel = ST::getIntern(node->method->name);

            return new CExpConverter(new IRT::CallExpression(methodLabel, args));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ConstExpression* node) const {
            return new CExpConverter(new IRT::ConstExpression(node->value));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BoolExpression* node) const {
            return new CExpConverter(new IRT::ConstExpression(node->value ? 1 : 0));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IdExpression* node) const {
            return node->id->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewArrayExpression* node) const {
            auto* addrHolder = new IRT::TempExpression(new TempReg());
            auto* allocArgs = new IRT::CExpressionList();
            auto* sizeExp = node->size->accept(this)->ToExp();
            auto* sizeForArrayStruct = new IRT::BinopExpression(sizeExp, IRT::BO_Plus, new IRT::ConstExpression(frame->GetWordSize()));
            allocArgs->nodes.emplace_back(sizeExp);
            auto* allocStm = new IRT::MoveStatement(addrHolder, frame->ExternalCall("newArray", allocArgs));

            auto* initSizeStm = new IRT::MoveStatement(addrHolder, sizeExp);
            // if it's needed to initialize it can be done there

            return new CExpConverter(new IRT::EseqExpression(new IRT::SeqStatement(allocStm, initSizeStm), addrHolder));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewObjectExpression* node) const {
            auto* addrHolder = new IRT::TempExpression(new TempReg());

            auto* allocArgs = new IRT::CExpressionList();
            auto* label = ST::getIntern(node->id->name);
            auto&& classVarsCount = table->getClassInfo(label)->getVars().size();
            auto sizeExp = new IRT::ConstExpression(static_cast<int>(classVarsCount));
            allocArgs->nodes.emplace_back(sizeExp);
            auto* allocStm = new IRT::MoveStatement(addrHolder, frame->ExternalCall("newObject", allocArgs));

            return new CExpConverter(new IRT::EseqExpression(allocStm, addrHolder));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NotExpression* node) const {
            auto* expSubtree = node->exp->accept(this);
            auto* one = new IRT::ConstExpression(1);
            return new CExpConverter(new IRT::BinopExpression(expSubtree->ToExp(), IRT::BO_Xor, one));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Identifier* node) const {
            auto* label = ST::getIntern(node->name);
            auto* access = frame->FindLocalOrFormal(label);
            if (auto* inRegAccess = dynamic_cast<const CInRegAccess*>(access)) {
                auto* temp = new IRT::TempExpression(inRegAccess->reg);
                return new CExpConverter(temp);
            }
            if (auto* inFrameAccess = dynamic_cast<const CInFrameAccess*>(access)) {
                auto* addr = new IRT::BinopExpression(frame->FramePointer(), IRT::BO_Plus,  inFrameAccess->getExp());
                auto* mem = new IRT::MemExpression(addr);
                return new CExpConverter(mem);
            }
            throw CantBuildIrtError();
        }

    }
}
