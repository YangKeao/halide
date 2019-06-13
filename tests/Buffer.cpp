#include "gtest/gtest.h"
#include "Buffer.h"

using namespace Halide;

TEST(Buffer, load_png) {
    auto buffer = load_png("../tests/parrot.png");
    assert(buffer.getWidth() == 256);
    assert(buffer.getHeight() == 426);
    assert(buffer(0, 0, 0) == 1);
    assert(buffer(0, 9, 0) == 28);
}