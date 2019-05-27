//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_EXPR_H
#define HALIDE_EXPR_H


#include <unitypes.h>
#include "Type.h"

namespace Halide {
    namespace Internal {
        template<typename T>
        struct ExprNode {

        };

        struct IntConst: ExprNode<IntConst> {
            static const IntConst *make(Type t, int64_t value);
        };

        struct UIntConst: ExprNode<UIntConst> {
            static const UIntConst *make(Type t, int64_t value);
        };

        struct FloatConst: ExprNode<FloatConst> {
            static const FloatConst *make(Type t, int64_t value);
        };
    }

    inline Type Int(int bits, int count = 1) {
        return Type(Type::Int, bits, count);
    }

    inline Type UInt(int bits, int count = 1) {
        return Type(Type::UInt, bits, count);
    }

    inline Type Float(int bits, int count = 1) {
        return Type(Type::Float, bits, count);
    }
}

#endif //HALIDE_EXPR_H
