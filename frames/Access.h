#pragma once

#include "Temp.h"

namespace frames {

    enum RecordType {
        RT_Formal,
        RT_Local,
        RT_FramePointer,
        RT_StackPointer,
        RT_AddressExit,
        RT_AddressReturnValue
    };

    struct IAccess {
        virtual ~IAccess() = 0;
        virtual const RecordType GetRecordType() = 0;
    };

    class CInRegAccess : public IAccess {
    public:
        CInRegAccess(RecordType type, int reg) : recType(type), reg(reg) {}
    private:
        const RecordType recType;
        int reg;
    };

    class CInFrameAccess : public IAccess {
    public:
        CInFrameAccess(RecordType type, int offset) : recType(type), address(offset) {}
        const Temp& Offset() const {
            return address;
        }
    private:
        const RecordType recType;
        const Temp address;
    };
}