//
// Created by yangkeao on 6/11/19.
//

#include "Buffer.h"
#include <cstdio>

namespace Halide {

    Buffer load_png(const std::string &filename) {
        char header[8];

        FILE *file = fopen(filename.c_str(), "rb");
        fread(header, 1, 8, file);

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        setjmp(png_jmpbuf(png_ptr));

        png_init_io(png_ptr, file);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        int width = png_get_image_width(png_ptr, info_ptr);
        int height = png_get_image_height(png_ptr, info_ptr);
        png_byte color_type = png_get_color_type(png_ptr, info_ptr);
        png_byte depth = png_get_bit_depth(png_ptr, info_ptr);

        auto* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (int y=0; y<height; y++)
            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        fclose(file);

        // TODO: Support RGBA and other color_type
        auto* raw_image = (RGB*) malloc(sizeof(RGB) * width * height);
        for (int y=0;y<height;y++) {
            for (int x = 0; x<width; x ++) {
                raw_image[y * width + x] = RGB {
                    row_pointers[y][x * depth],
                    row_pointers[y][x * depth + 1],
                    row_pointers[y][x * depth + 2],
                };
            }
        }

        return Buffer(width, height, depth, raw_image);
    }

    Buffer::Buffer(int width, int height, unsigned char depth, RGB *rawImage) : width(width), height(height), depth(depth),
                                                                       raw_image(rawImage) {}

    int Buffer::getWidth() const {
        return width;
    }

    int Buffer::getHeight() const {
        return height;
    }

    unsigned char Buffer::getDepth() const {
        return depth;
    }

    unsigned char Buffer::operator()(int x, int y, int c) const {
        return *((unsigned char *) (this->raw_image + y * width + x) + c);
    }
}