//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_EXPR_H
#define HALIDE_EXPR_H

#include "Type.h"

namespace Halide {
    class Expr {
      public:
        Expr() = default;

        template<typename T>
        friend Expr operator+(Expr lhs, T rhs);

        template<typename T>
        friend Expr operator-(Expr lhs, T rhs);

        template<typename T>
        friend Expr operator*(Expr lhs, T rhs);

        template<typename T>
        friend Expr operator/(Expr lhs, T rhs);
    };
}

#endif //HALIDE_EXPR_H
