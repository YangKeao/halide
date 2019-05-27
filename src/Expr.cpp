//
// Created by yangkeao on 5/27/19.
//

#include "Expr.h"

namespace Halide {

    namespace Internal {
        const IntConst *IntConst::make(Type t, int64_t value) {
            return nullptr;
        }

        const UIntConst *UIntConst::make(Type t, int64_t value) {
            return nullptr;
        }

        const FloatConst *FloatConst::make(Type t, int64_t value) {
            return nullptr;
        }
    }
}
