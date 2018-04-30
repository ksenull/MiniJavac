#pragma once

#include "../symboltable/Symbol.h"

namespace frames {

    namespace ST = symboltable;
    struct IAccess {
            // Пока интерфейс пуст
            virtual ~IAccess() = 0;
    };

    class CInRegAccess : public IAccess {

    };

    class CInFrameAccess : public IAccess {

    };

    struct IFrame {
            virtual void AddFormal( const ST::Symbol* name, ...) = 0;
            virtual void AddLocal( const ST::Symbol* name, ...) = 0;
            virtual int FormalsCount() const = 0;
            virtual const IAccess* Formal( int index ) const = 0;
            virtual const IAccess* FindLocalOrFormal( const ST::Symbol* name ) const = 0;
    };
}