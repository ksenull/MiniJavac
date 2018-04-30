#pragma once

#include "Temp.h"

namespace frames {

    enum RecordType {
        RT_Formal,
        RT_Local,
        RT_FramePointer,
        RT_StackPointer,
        RT_ReturnAddress,
        RT_ReturnValue
    };

    struct IAccess {
        virtual ~IAccess() = default;
    };

    class CInRegAccess : public IAccess {
    public:
        CInRegAccess(RecordType type, int reg, int size) : recType(type), reg(reg), size(size) {}
        ~CInRegAccess() = default;
    private:
        const RecordType recType;
        TempReg reg;
        const int size;
    };

    class CInFrameAccess : public IAccess {
    public:
        CInFrameAccess(RecordType type, int offset, int size) : recType(type), offset(offset), size(size) {}
        ~CInFrameAccess() = default;
    private:
        const RecordType recType;
        const int offset; // offset from the FP
        const int size;
    };
}