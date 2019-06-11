//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_FUNC_H
#define HALIDE_FUNC_H

#include <vector>
#include "Var.h"
#include "Expr.h"

namespace Halide {
    class Func {
        bool definition = false;
        std::vector<Var> args;
      public:
        Func() = default;
        Func(bool definition, const std::vector<Var> &args);

        Func operator()(std::vector<Var>) const;

        template <typename... Args>
        Func operator()(Args&&... args) const;

        const Func operator=(Expr) const;
    };

    template<typename... Args>
    Func Func::operator()(Args &&... args) const {
        std::vector<Var> collected_args{std::forward<Args>(args)...};
        return this->operator()(collected_args);
    }
}


#endif //HALIDE_FUNC_H
