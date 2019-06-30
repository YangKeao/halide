//
// Created by yangkeao on 5/27/19.
//

#include "gtest/gtest.h"
#include "Halide.h"

using namespace Halide;

TEST(Func, Func) {
    Var x, y, z;
    Func average;

    average(x, y, z) = x + 100;

    auto ctx = CompileCtx();
    auto output = average.realize(100, 100, 0, 0);

    output.write_to("parrot.png");
    assert(output.get(5, 5, 1) == 105);
}
