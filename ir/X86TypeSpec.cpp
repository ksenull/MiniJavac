//
// Created by ksenull on 4/30/18.
//
#include <cassert>
#include "ITypeSpec.h"

namespace ir {
    namespace ST = symboltable;

    static const int WORD_SIZE = 4;
    static const int intSize = 1 * WORD_SIZE;
    static const int booleanSize = 1 * WORD_SIZE;
    static const int referenceSize = 1 * WORD_SIZE;

    int DefaultTypeSpec::getTypeSize(ST::VariableType type) const {
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

    int DefaultTypeSpec::getRefSize() const {
        return referenceSize;
    }

   int DefaultTypeSpec::getWordSize() const {
       return WORD_SIZE;
   }
}
