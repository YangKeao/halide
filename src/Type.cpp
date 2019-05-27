//
// Created by yangkeao on 5/27/19.
//

#include "Type.h"

Halide::Type::Type(Halide::type_code code, unistring_uint8_t bits, unistring_uint16_t count) : code(code), bits(bits),
                                                                                               count(count) {}
