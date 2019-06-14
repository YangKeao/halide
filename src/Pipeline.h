//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_PIPELINE_H
#define HALIDE_PIPELINE_H

#include "Func.h"

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

        Buffer realize();
    };
}


#endif //HALIDE_PIPELINE_H
