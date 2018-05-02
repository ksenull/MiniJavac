#pragma once

#include "Temp.h"
#include "tree/Expressions.h"

namespace ir {

    enum RecordType {
        RT_Formal,
        RT_Local,
        RT_ReturnAddress,
        RT_ReturnValue,
        RT_FramePointer,
        RT_StackPointer
    };

    inline std::string recordTypeToString(RecordType type) {
        switch (type) {
            case RT_Formal:
                return "#formal#";
            case RT_Local:
                return "#local#";
            case RT_ReturnAddress:
                return "#return_address#";
            case RT_ReturnValue:
                return "#return_value";
            case RT_FramePointer:break;
            case RT_StackPointer:break;
        }
    }

    struct IAccess {
        virtual ~IAccess() = default;
        virtual std::string str() const = 0;

        virtual tree::IExpression* getExp() const = 0;
    };

    class CInRegAccess : public IAccess {
    public:
        CInRegAccess(RecordType type, int size, int initialValue) : recType(type), size(size) {
            reg = new SpecialReg(initialValue);
        }
        CInRegAccess(RecordType type, int size) : recType(type), size(size) {
            reg = new TempReg();
        }
        std::string str() const override {
            std::stringstream ss;
            ss << "reg##";
            ss << " - " << size << " bytes";
            return recordTypeToString(recType) + ss.str();
        }
        ~CInRegAccess() = default;

        tree::IExpression* getExp() const override {
            return new tree::TempExpression(reg);
        }

        IReg* reg;
    private:
        const RecordType recType;
        const int size;
    };

    class CInFrameAccess : public IAccess {
    public:
        CInFrameAccess(RecordType type, int offset, int size) : recType(type), offset(offset), size(size) {}
        std::string str() const override {
            std::stringstream ss;
            ss << "FP-" << offset << "##";
            ss << " - " << size << " bytes";
            return recordTypeToString(recType) + ss.str();
        }
        ~CInFrameAccess() = default;

        tree::IExpression* getExp() const override {
            return new tree::ConstExpression(offset);
        }
    private:
        const RecordType recType;
        const int offset; // offset from the FP
        const int size;
    };
}