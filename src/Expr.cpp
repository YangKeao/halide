//
// Created by yangkeao on 5/27/19.
//

#include "Expr.h"
#include "Const.h"

namespace Halide {

    Expr operator+(Expr lhs, const Expr &rhs) {
        return AddExpr(lhs, rhs);
    }

    Expr operator-(Expr lhs, const Expr &rhs) {
        return MinusExpr(lhs, rhs);
    }

    Expr operator*(Expr lhs, const Expr &rhs) {
        return MulExpr(lhs, rhs);
    }

    Expr operator/(Expr lhs, const Expr &rhs) {
        return DivExpr(lhs, rhs);
    }

    Expr operator+(Expr lhs, int rhs) {
        return AddExpr(lhs, ConstInt(rhs));
    }
    Expr operator-(Expr lhs, int rhs) {
        return MinusExpr(lhs, ConstInt(rhs));
    }
    Expr operator*(Expr lhs, int rhs) {
        return MulExpr(lhs, ConstInt(rhs));
    }
    Expr operator/(Expr lhs, int rhs) {
        return DivExpr(lhs, ConstInt(rhs));
    }

    Expr operator+(Expr lhs, unsigned int rhs) {
        return AddExpr(lhs, ConstUInt(rhs));
    }
    Expr operator-(Expr lhs, unsigned int rhs) {
        return MinusExpr(lhs, ConstUInt(rhs));
    }
    Expr operator*(Expr lhs, unsigned int rhs) {
        return MulExpr(lhs, ConstUInt(rhs));
    }
    Expr operator/(Expr lhs, unsigned int rhs) {
        return DivExpr(lhs, ConstUInt(rhs));
    }

    Expr operator+(Expr lhs, float rhs) {
        return AddExpr(lhs, ConstFloat(rhs));
    }
    Expr operator-(Expr lhs, float rhs) {
        return MinusExpr(lhs, ConstFloat(rhs));
    }
    Expr operator*(Expr lhs, float rhs) {
        return MulExpr(lhs, ConstFloat(rhs));
    }
    Expr operator/(Expr lhs, float rhs) {
        return DivExpr(lhs, ConstFloat(rhs));
    }

    AddExpr::AddExpr(const Expr &lhs, const Expr &rhs) : lhs(lhs), rhs(rhs) {}

    MinusExpr::MinusExpr(const Expr &lhs, const Expr &rhs) : lhs(lhs), rhs(rhs) {}

    MulExpr::MulExpr(const Expr &lhs, const Expr &rhs) : lhs(lhs), rhs(rhs) {}

    DivExpr::DivExpr(const Expr &lhs, const Expr &rhs) : lhs(lhs), rhs(rhs) {}
}
