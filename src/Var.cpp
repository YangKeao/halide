//
// Created by yangkeao on 5/27/19.
//

#include "Var.h"
#include "Util.h"

namespace Halide {
    Var::Var(const std::string &n) : _name(n) {
    }

    Var::Var() : _name(Internal::make_entity_name('v')) {
    }

    void *Var::codegen(CompileCtx& ctx) {
        return ctx.llvm_named_values[name()];
    }
}
