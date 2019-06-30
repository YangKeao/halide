//
// Created by yangkeao on 6/14/19.
//

#include "Pipeline.h"
#include "OpExpr.h"

namespace Halide {

    Pipeline::Pipeline(Func &mainFunc, int offsetX, int offsetY, int width, int height) : main_func(mainFunc),
                                                                                          offset_x(offsetX),
                                                                                          offset_y(offsetY),
                                                                                          width(width),
                                                                                          height(height), ctx() {}

    Buffer Pipeline::realize() {
//        auto main_func = this->main_func.codegen(this->ctx);
        auto size = sizeof(RGB) * width * height;

        auto output_buffer = (RGB*)malloc(size);
        auto array_type = llvm::ArrayType::get(llvm::Type::getInt8PtrTy(ctx.llvm_context), size);
        auto buffer = new llvm::GlobalVariable(
                *ctx.llvm_module.get(),
                array_type,
                false,
                llvm::GlobalValue::ExternalWeakLinkage,
                0,
                "__output_buffer__"
        );

        auto func_type = llvm::FunctionType::get(llvm::FunctionType::getVoidTy(this->ctx.llvm_context), false);
        auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "__call_point__",
                                           ctx.llvm_module.get());

        {
            llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(ctx.llvm_context, "entry", func);
            ctx.llvm_builder.SetInsertPoint(basic_block);

            auto x = this->main_func.args.get()->at(0);
            auto y = this->main_func.args.get()->at(1);
            auto c = this->main_func.args.get()->at(2);

            create_loop([&]() {
                create_loop([&]() {
                    create_loop([&]() {
                        auto val = (llvm::Value *)this->main_func.impls->codegen(ctx);
                        auto val_8bit = ctx.llvm_builder.CreateIntCast(val, llvm::Type::getInt8Ty(ctx.llvm_context), false);

//                        auto buffer_ptr = ctx.llvm_builder.CreateLoad(buffer, "__load_tmp__");

                        auto offset = (llvm::Value *) ((((y - offset_y) * width) +  (x - offset_x)) * ((int)sizeof(RGB)) + c).codegen(ctx);
                        auto rgb_ptr = ctx.llvm_builder.CreateAlloca(llvm::Type::getInt8PtrTy(ctx.llvm_context));
                        ctx.llvm_builder.CreateGEP(array_type, rgb_ptr, offset, "__gep_tmp__");
                        ctx.llvm_module->print(llvm::errs(), nullptr);
                        ctx.llvm_builder.CreateStore(val_8bit, rgb_ptr);
                    }, c, Bound(0, 3), Const(1));
                }, y, Bound(offset_y, offset_y + height), Const(1));
            }, x, Bound(offset_x, offset_x + width), Const(1));
        }

        ctx.llvm_builder.CreateRetVoid();

        ctx.llvm_module->print(llvm::errs(), nullptr);

        JIT engine(std::move(ctx.llvm_module));

        engine.map_var("__output_buffer__", (uint64_t) output_buffer);
        for(auto & i : ctx.llvm_global_map) {
            engine.map_var(i.first, (uint64_t) &i.second);
        }

        engine.run();

        return Buffer(width, height, 24, output_buffer);
    }

    template<typename T>
    void Pipeline::create_loop(std::function<void()> insert_body, Var iter_var, Bound<T> bound, Const<T> step) {
        Const start(bound.getStart());
        Const end(bound.getEnd());

        auto function = ctx.llvm_builder.GetInsertBlock()->getParent();

        auto iter = ctx.llvm_builder.CreateAlloca(llvm::Type::getInt32Ty(ctx.llvm_context), (llvm::Value *)Const(4).codegen(ctx), iter_var.name());
        ctx.llvm_builder.CreateStore((llvm::Value *)start.codegen(ctx), iter);

        auto check_block = llvm::BasicBlock::Create(ctx.llvm_context, "__check_block__", function);
        auto body_block = llvm::BasicBlock::Create(ctx.llvm_context, "__body_block__", function);
        auto after_block = llvm::BasicBlock::Create(ctx.llvm_context, "__after_loop__", function);
        ctx.llvm_builder.CreateBr(check_block);
        ctx.llvm_builder.SetInsertPoint(check_block);
        auto iter_value = ctx.llvm_builder.CreateLoad(iter, "__load__");
        ctx.llvm_named_values[iter_var.name()] = iter_value;
        auto *end_cond = ctx.llvm_builder.CreateICmpSLT(iter_value, (llvm::Value *) end.codegen(ctx));
        ctx.llvm_builder.CreateCondBr(end_cond, body_block, after_block);

        ctx.llvm_builder.SetInsertPoint(body_block);
        insert_body();
        auto *step_val = (llvm::Value *) step.codegen(ctx);
        auto *next = ctx.llvm_builder.CreateAdd(iter_value, step_val);
        ctx.llvm_builder.CreateStore(next, iter);
        ctx.llvm_builder.CreateBr(check_block);

        ctx.llvm_builder.SetInsertPoint(after_block);
    }
}