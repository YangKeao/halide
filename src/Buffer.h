//
// Created by yangkeao on 6/11/19.
//

#ifndef HALIDE_BUFFER_H
#define HALIDE_BUFFER_H

#include <png.h>
#include <string>
#include "Expr.h"

namespace Halide {
    struct RGB {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

    class BufferCall;

    class Buffer {
      private:
        int width;
        int height;
        unsigned char depth;

        RGB* raw_image;
      public:
        RGB *getRawImage() const;

      public:
        Buffer(int width, int height, unsigned char depth, RGB *rawImage);

        void write_to(const std::string &filename);

        int getWidth() const;

        int getHeight() const;

        unsigned char getDepth() const;

        unsigned char get(int x, int y, int c) const;

        BufferCall& operator()(Expr& x, Expr& y, Expr& c) const;
    };

    class BufferCall: public Expr {
      private:
        const Buffer& buf;
        Expr& x;
        Expr& y;
        Expr& c;

      public:
        BufferCall(const Buffer &buf, Expr &x, Expr &y, Expr &c);

        void *codegen(CompileCtx &ctx) override;
    };

    Buffer load_png(const std::string &filename);
}


#endif //HALIDE_BUFFER_H
