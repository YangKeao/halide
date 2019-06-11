//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_FUNC_H
#define HALIDE_FUNC_H

#include <vector>
#include <memory>
#include "Var.h"
#include "Expr.h"

namespace Halide {
    class Func {
        bool definition = false;
        std::unique_ptr<Expr> impls = nullptr;
        std::unique_ptr<std::vector<Var>> args;
      public:
        Func() = default;

        Func& operator()(std::vector<Var>);

        template <typename... Args>
        Func& operator()(Args&&... args);

        Func& operator=(Expr);
    };

    template<typename... Args>
    Func& Func::operator()(Args &&... args) {
        std::vector<Var> collected_args{std::forward<Args>(args)...};
        return this->operator()(collected_args);
    }
}


#endif //HALIDE_FUNC_H
