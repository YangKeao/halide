//
// Created by yangkeao on 6/14/19.
//

#include "Pipeline.h"

namespace Halide {

    Pipeline::Pipeline(Func &mainFunc, int offsetX, int offsetY, int width, int height) : main_func(mainFunc),
                                                                                                offset_x(offsetX),
                                                                                                offset_y(offsetY),
                                                                                                width(width),
                                                                                                height(height), ctx() {}

    Buffer Pipeline::realize() {

        return Buffer(0, 0, 0, nullptr);
    }
}