//
// Created by yangkeao on 5/27/19.
//

#include "gtest/gtest.h"
#include "Func.h"

using namespace Halide;

TEST(Func, Func) {
    Var x, y, z;
    Func average;

    average(x, y, z) = (x + y + z) / 2;
}
