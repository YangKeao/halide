//
// Created by yangkeao on 6/11/19.
//

#include "Const.h"

namespace Halide {
    ConstInt::ConstInt(int value) : value(value){

    }

    ConstUInt::ConstUInt(unsigned int value) : value(value){

    }

    ConstFloat::ConstFloat(float value) : value(value){

    }
}
