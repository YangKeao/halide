//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_EXPR_H
#define HALIDE_EXPR_H


#include <unitypes.h>
#include "Type.h"

namespace Halide {
    class Expr {
      public:
        Expr() = default;

        friend Expr operator+(Expr lhs, const Expr& rhs);
        friend Expr operator-(Expr lhs, const Expr& rhs);
        friend Expr operator*(Expr lhs, const Expr& rhs);
        friend Expr operator/(Expr lhs, const Expr& rhs);

        friend Expr operator+(Expr lhs, int rhs);
        friend Expr operator-(Expr lhs, int rhs);
        friend Expr operator*(Expr lhs, int rhs);
        friend Expr operator/(Expr lhs, int rhs);

        friend Expr operator+(Expr lhs, unsigned int rhs);
        friend Expr operator-(Expr lhs, unsigned int rhs);
        friend Expr operator*(Expr lhs, unsigned int rhs);
        friend Expr operator/(Expr lhs, unsigned int rhs);

        friend Expr operator+(Expr lhs, float rhs);
        friend Expr operator-(Expr lhs, float rhs);
        friend Expr operator*(Expr lhs, float rhs);
        friend Expr operator/(Expr lhs, float rhs);
    };

    class AddExpr: public Expr {
      private:
        Expr lhs;
        Expr rhs;

      public:
        AddExpr(const Expr &lhs, const Expr &rhs);
    };

    class MinusExpr: public Expr {
      private:
        Expr lhs;
        Expr rhs;

      public:
        MinusExpr(const Expr &lhs, const Expr &rhs);
    };

    class MulExpr: public Expr {
      private:
        Expr lhs;
        Expr rhs;

      public:
        MulExpr(const Expr &lhs, const Expr &rhs);
    };

    class DivExpr: public Expr {
      private:
        Expr lhs;
        Expr rhs;

      public:
        DivExpr(const Expr &lhs, const Expr &rhs);
    };
}

#endif //HALIDE_EXPR_H
