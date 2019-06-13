//
// Created by yangkeao on 6/11/19.
//

#ifndef HALIDE_BUFFER_H
#define HALIDE_BUFFER_H

#include <png.h>
#include <string>

namespace Halide {
    struct RGB {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    class Buffer {
      private:
        int width;
        int height;
        unsigned char depth;

        RGB* raw_image;

      public:
        Buffer(int width, int height, unsigned char depth, RGB *rawImage);

        void write_to(const std::string &filename);

        int getWidth() const;

        int getHeight() const;

        unsigned char getDepth() const;

        unsigned char operator()(int x, int y, int c) const;

    };

    Buffer load_png(const std::string &filename);
}


#endif //HALIDE_BUFFER_H
