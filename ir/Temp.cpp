//
// Created by ksenull on 5/2/18.
//
#include "Temp.h"

namespace ir {
    int TempReg::counter = 0;

    int SpecialLabel::counter = 0;

    std::string SpecialReg::str() {
        switch (type) {
            case SRT_FP:
                return "FP";
            case SRT_SP:
                return "SP";
            case SRT_RV:
                return "RVReg";
        }
    }
}
