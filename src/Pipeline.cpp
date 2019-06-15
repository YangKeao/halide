//
// Created by yangkeao on 6/14/19.
//

#include "Pipeline.h"

namespace Halide {

    Pipeline::Pipeline(Func &mainFunc, int offsetX, int offsetY, int width, int height) : main_func(mainFunc),
                                                                                                offset_x(offsetX),
                                                                                                offset_y(offsetY),
                                                                                                width(width),
                                                                                                height(height), ctx() {}

    Buffer Pipeline::realize() {
        auto main_func = this->main_func.codegen(this->ctx);

        {
            auto func_type = llvm::FunctionType::get(llvm::FunctionType::getVoidTy(this->ctx.llvm_context), false);
            auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "__call_point__", ctx.llvm_module.get());

            llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(ctx.llvm_context, "entry", func);
            ctx.llvm_builder.SetInsertPoint(basic_block);
        }

        return Buffer(0, 0, 0, nullptr);
    }
}