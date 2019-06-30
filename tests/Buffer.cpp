#include "gtest/gtest.h"
#include "Halide.h"

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

TEST(Buffer, blur) {
    Var x,y,c, x_outer, x_inner, tile_index;
    Func blur;
    auto buffer = load_png("../tests/parrot.png");

    int r = 1;
    for (int i=-r;i<=r;i++) {
        for (int j=-r;j<=r;j++) {
            blur(x, y, c) += buffer(x + i, y + j, c);
        }
    }
    blur(x, y, c) /= (2 * r + 1) * (2 * r + 1);

    blur.split(x, x_outer, x_inner, 8);
    blur.reorder(c, x_inner, x_outer, y);
    blur.fuse(x_inner, c, tile_index);
    blur.vectorized(tile_index, 32);

    auto output = blur.realize(buffer.getWidth() - 2 *r, buffer.getHeight() - 2 * r, r, r);
    output.write_to("./parrot.png");
}