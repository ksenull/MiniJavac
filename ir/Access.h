#pragma once

#include "Temp.h"

namespace ir {

    enum RecordType {
        RT_Formal,
        RT_Local,
        RT_ReturnAddress,
        RT_ReturnValue
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
        }
    }

    struct IAccess {
        virtual ~IAccess() = default;
        virtual std::string str() const = 0;
    };

    class CInRegAccess : public IAccess {
    public:
        CInRegAccess(RecordType type, int reg, int size) : recType(type), reg(reg), size(size) {}
        std::string str() const override {
            std::stringstream ss;
            ss << "reg##" << reg.num << "##";
            ss << " - " << size << " bytes";
            return recordTypeToString(recType) + ss.str();
        }
        ~CInRegAccess() = default;
    private:
        const RecordType recType;
        TempReg reg;
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
    private:
        const RecordType recType;
        const int offset; // offset from the FP
        const int size;
    };
}