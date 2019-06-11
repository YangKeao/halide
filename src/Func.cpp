//
// Created by yangkeao on 5/27/19.
//

#include "Func.h"

namespace Halide {
    Func& Func::operator=(Expr impls) {
        auto new_ptr = std::make_unique<Expr>(impls);
        this->impls.swap(new_ptr);
        return *this;
    }

    Func& Func::operator()(std::vector<Var> args) {
        auto new_ptr = std::make_unique<std::vector<Var>>(args);
        this->args.swap(new_ptr);
        return *this;
    }
}
