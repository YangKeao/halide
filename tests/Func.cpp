//
// Created by yangkeao on 5/27/19.
//

#include "gtest/gtest.h"
#include "Halide.h"

using namespace Halide;

TEST(Func, Func) {
    Var x, y, z;
    Func average;

    average(x, y, z) = (x + y + z);
    average /= 3;
}
