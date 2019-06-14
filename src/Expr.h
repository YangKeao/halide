//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_EXPR_H
#define HALIDE_EXPR_H

#include "Type.h"
#include "CompileCtx.h"

namespace Halide {

    class Expr {
      public:
        Expr() = default;

        template<typename T>
        friend Expr& operator+(Expr& lhs, T rhs);

        template<typename T>
        friend Expr& operator-(Expr& lhs, T rhs);

        template<typename T>
        friend Expr& operator*(Expr& lhs, T rhs);

        template<typename T>
        friend Expr& operator/(Expr& lhs, T rhs);

        virtual void* codegen(CompileCtx&) = 0;
    };
}

#endif //HALIDE_EXPR_H
