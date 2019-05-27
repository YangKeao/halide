//
// Created by yangkeao on 5/27/19.
//

#include "gtest/gtest.h"
#include "Var.h"

TEST(Var, Var_Construc_Test) {
    Halide::Var x, y, z("test"),q("test");
    assert(!x.same_as(y));
    assert(z.same_as(q));
}
