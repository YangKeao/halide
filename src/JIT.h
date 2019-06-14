//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_JIT_H
#define HALIDE_JIT_H

#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/Interpreter.h"


namespace Halide {
    class JIT {
      public:
        JIT() {
        }
    };
}


#endif //HALIDE_JIT_H
