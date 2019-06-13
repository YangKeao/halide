//
// Created by yangkeao on 6/13/19.
//

#ifndef HALIDE_OPEXPR_H
#define HALIDE_OPEXPR_H


#include "Const.h"

namespace Halide {
    enum Op {
        Add,
        Minus,
        Mul,
        Div,
    };

    template<Op op>
    class OpExpr: public Expr {
      private:
        Expr lhs;
        Expr rhs;
        Op _op = op;
      public:
        Op getOp() const {
            return _op;
        }

        template<typename T>
        OpExpr(const Expr &lhs, T& rhs): lhs(lhs), rhs(Const(rhs)) {}
    };



    template<typename T>
    Expr operator+(Expr lhs, T rhs) {
        return OpExpr<Op::Add>(lhs, rhs);
    }

    template<typename T>
    Expr operator-(Expr lhs, T rhs) {
        return OpExpr<Op::Minus>(lhs, rhs);
    }

    template<typename T>
    Expr operator*(Expr lhs, T rhs) {
        return OpExpr<Op::Mul>(lhs, rhs);
    }

    template<typename T>
    Expr operator/(Expr lhs, T rhs) {
        return OpExpr<Op::Div>(lhs, rhs);
    }
}


#endif //HALIDE_OPEXPR_H
