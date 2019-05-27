//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_TYPE_H
#define HALIDE_TYPE_H


#include <unitypes.h>

namespace Halide {
    enum type_code {
        type_int = 0,
        type_uint = 1,
        type_float = 2,
        type_ptr = 3,
    };

    class Type {
      private:
        type_code code;
        uint8_t bits;
        uint16_t count;
      public:
        static const type_code Int = type_code::type_int;
        static const type_code UInt = type_code::type_uint;
        static const type_code Float = type_code::type_float;
        static const type_code Ptr = type_code::type_ptr;

        Type(type_code code, unistring_uint8_t bits, unistring_uint16_t count);
    };
}


#endif //HALIDE_TYPE_H
