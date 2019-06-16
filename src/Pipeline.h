//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_PIPELINE_H
#define HALIDE_PIPELINE_H

#include "Func.h"
#include "Bound.h"
#include "Const.h"
#include "JIT.h"

namespace Halide {
    class Pipeline {
      private:
        Func& main_func;
        int offset_x;
        int offset_y;
        int width;
        int height;

        CompileCtx ctx;

      public:
        Pipeline(Func &mainFunc, int offsetX, int offsetY, int width, int height);

        template<typename T>
        void create_loop(std::function<void()> insert_body, Var iter_var, Bound<T> bound, Const<T> step);

        Buffer realize();
    };
}

#endif //HALIDE_PIPELINE_H
