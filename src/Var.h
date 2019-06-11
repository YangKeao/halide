//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_VAR_H
#define HALIDE_VAR_H

#include <string>
#include "Expr.h"

namespace Halide {
    class Var: public Expr {
        std::string _name;
      public:
        explicit Var(const std::string &n);

        Var();

        bool same_as(const Var &other) const {return _name == other._name;}

        const std::string &name() const {return _name;}
    };
}

#endif //HALIDE_VAR_H
