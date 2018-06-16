//
// Created by ksenull on 4/30/18.
//
#include <cassert>
#include "ITypeSpec.h"

namespace ir {
    namespace ST = symboltable;

    static const unsigned WORD_SIZE = 4;
    static const unsigned intSize = 1 * WORD_SIZE;
    static const unsigned booleanSize = 1 * WORD_SIZE;
    static const unsigned referenceSize = 1 * WORD_SIZE;

    unsigned DefaultTypeSpec::getTypeSize(ST::VariableType type) const {
        switch (type) {
            case ST::VT_Int:
                return intSize;
            case ST::VT_IntArray:
                return referenceSize;
            case ST::VT_Boolean:
                return booleanSize;
            case ST::VT_Object:
                return referenceSize;
            default:
                assert(false);
        }
    }

    unsigned DefaultTypeSpec::getRefSize() const {
        return referenceSize;
    }

    unsigned DefaultTypeSpec::getWordSize() const {
       return WORD_SIZE;
    }
}
