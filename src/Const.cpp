//
// Created by yangkeao on 6/11/19.
//

#include "Const.h"
#include "Var.h"

namespace Halide {
    template<>
    void* Const<int>::codegen(CompileCtx& ctx) {
        return llvm::ConstantInt::get(ctx.llvm_context, llvm::APInt(32, value, true));
    }

    template<>
    void* Const<float>::codegen(CompileCtx& ctx) {
        return llvm::ConstantFP::get(ctx.llvm_context, llvm::APFloat(value));
    }

    template<>
    void* Const<unsigned char>::codegen(CompileCtx& ctx) {
        return llvm::ConstantInt::get(ctx.llvm_context, llvm::APInt(8, value, false));
    }

    template<>
    void* Const<Var>::codegen(CompileCtx& ctx) {
        return value.codegen(ctx);
    }
}
