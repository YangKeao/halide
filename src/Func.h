//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_FUNC_H
#define HALIDE_FUNC_H

#include <vector>
#include "Var.h"

namespace Halide {
    class Func {
      public:
        Func operator()(std::vector<Var>) const;
    };
}


#endif //HALIDE_FUNC_H
