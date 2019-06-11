//
// Created by yangkeao on 5/27/19.
//

#include "Func.h"

namespace Halide {
    const Func Func::operator=(Expr) const {
        return Func(true, args);
    }

    Func Func::operator()(std::vector<Var> args) const {
        return Func(this->definition, args);
    }

    Func::Func(bool definition, const std::vector<Var> &args): definition(definition), args(args) {}
}
