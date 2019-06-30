//
// Created by yangkeao on 6/11/19.
//

#include "Buffer.h"
#include "OpExpr.h"
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
                    row_pointers[y][x * 3],
                    row_pointers[y][x * 3 + 1],
                    row_pointers[y][x * 3 + 2],
                };
            }
        }

        for (int y=0; y<height; y++)
            free(row_pointers[y]);

        free(row_pointers);

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

    unsigned char Buffer::get(int x, int y, int c) const {
        return *((unsigned char *) (this->raw_image + y * width + x) + c);
    }

    void Buffer::write_to(const std::string &filename) {
        FILE *file = nullptr;
        png_structp png_ptr = nullptr;
        png_infop info_ptr = nullptr;

        file = std::fopen(filename.c_str(), "wb");

        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        info_ptr = png_create_info_struct(png_ptr);
        setjmp(png_jmpbuf(png_ptr));

        png_init_io(png_ptr, file);

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        png_write_info(png_ptr, info_ptr);

        auto* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (int y=0; y<height; y++) {
            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
            for (int x=0;x<width;x++) {
                row_pointers[y][x * 3] = this->raw_image[y * width + x].red;
                row_pointers[y][x * 3 + 1] = this->raw_image[y * width + x].green;
                row_pointers[y][x * 3 + 2] = this->raw_image[y * width + x].blue;
            }
        }

        png_write_image(png_ptr, row_pointers);
        png_write_end(png_ptr, nullptr);
        png_destroy_write_struct(&png_ptr, (png_infopp)nullptr);

        for (int y=0; y<height; y++)
            free(row_pointers[y]);

        free(row_pointers);

        fclose(file);
    }

    BufferCall& Buffer::operator()(Expr& x, Expr& y, Expr& c) const {
        return *(new BufferCall(*this, x, y, c));
    }

    RGB *Buffer::getRawImage() const {
        return raw_image;
    }

    BufferCall::BufferCall(const Buffer &buf, Expr &x, Expr &y, Expr &c) : buf(buf), x(x), y(y), c(c) {}

    void *BufferCall::codegen(CompileCtx &ctx) {
        auto addr = (unsigned long) this->buf.getRawImage();
        auto buffer_name = "__buffer_" + std::to_string(addr) + "__";

        auto input_buffer = ctx.llvm_named_values[buffer_name];
        if (input_buffer == nullptr) {
            input_buffer = new llvm::GlobalVariable(
                    *ctx.llvm_module.get(),
                    llvm::Type::getInt8PtrTy(ctx.llvm_context),
                    false,
                    llvm::GlobalValue::ExternalWeakLinkage,
                    0,
                    buffer_name
            );
            ctx.llvm_global_map[buffer_name] = (unsigned long) (&this->buf);
            ctx.llvm_named_values[buffer_name] = input_buffer;
        }

        auto buffer_ptr = ctx.llvm_builder.CreateLoad(input_buffer, "__load_tmp__");
        auto rgb_ptr = ctx.llvm_builder.CreateGEP(buffer_ptr, (llvm::Value *) (((y * this->buf.getWidth()) +  x) * ((int)sizeof(RGB)) + c).codegen(ctx),
                                                  "__buffer_gep__");
        auto rgb = ctx.llvm_builder.CreateLoad(rgb_ptr, "__load_tmp__");
        return ctx.llvm_builder.CreateIntCast(rgb, llvm::Type::getInt32Ty(ctx.llvm_context), true, "__cast_tmp__");
    }
}