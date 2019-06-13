//
// Created by yangkeao on 5/27/19.
//

#include "Func.h"

namespace Halide {
    Func& Func::operator=(Expr impls) {
        this->impls = impls;
        return *this;
    }

    Func& Func::operator()(std::vector<Var> args) {
        auto new_ptr = std::make_unique<std::vector<Var>>(args);
        this->args.swap(new_ptr);
        return *this;
    }
}
