//
// Created by yangkeao on 6/11/19.
//

#ifndef HALIDE_CONST_H
#define HALIDE_CONST_H


#include "Expr.h"

namespace Halide {
    template <typename T>
    class Const : public Expr {
      private:
        T value;
      public:
        Const<T>(T value): value(value) {}
    };
}


#endif //HALIDE_CONST_H
