#include "gtest/gtest.h"
#include "Buffer.h"

using namespace Halide;

TEST(Buffer, load_png) {
    auto buffer = load_png("../tests/parrot.png");
    assert(buffer.getWidth() == 256);
    assert(buffer.getHeight() == 426);
    assert(buffer.get(0, 0, 0) == 1);
    assert(buffer.get(0, 9, 0) == 28);
    assert(buffer.get(0, 100, 0) == 5);
    assert(buffer.get(105, 105, 0) == 62);
}

TEST(Buffer, write_png) {
    auto buffer = load_png("../tests/parrot.png");

    buffer.write_to("./parrot(2).png");
    auto buffer2 = load_png("./parrot(2).png");

    assert(buffer2.getWidth() == 256);
    assert(buffer2.getHeight() == 426);
    assert(buffer2.getDepth() == 8);
    for (int x=0;x<256;x++) {
        for (int y=0;y<426;y++) {
            for (int c=0;c<3;c++) {
                assert(buffer.get(x, y, c) == buffer2.get(x, y, c));
            }
        }
    }

    unlink("./parrot(2).png");
}