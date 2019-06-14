//
// Created by yangkeao on 5/27/19.
//

#include "Func.h"
#include "Pipeline.h"

namespace Halide {
    Func& Func::operator=(Expr& impls) {
        this->definition = true;
        this->impls = (Expr*)&impls;
        return *this;
    }

    Func& Func::operator()(std::vector<Var> args) {
        auto new_ptr = std::make_unique<std::vector<Var>>(args);
        this->args.swap(new_ptr);
        return *this;
    }

    Buffer Func::realize(int width, int height, int offsetX, int offsetY) {
        auto pipeline = Pipeline(*this, offsetX, offsetY, width, height);
        return pipeline.realize();
    }

    void* Func::codegen(CompileCtx& ctx) {
        if (this->isDefinition()) {
            std::vector<llvm::Type*> arg_types(this->args.get()->size(), llvm::Type::getInt32Ty(ctx.llvm_context));

            auto func_type = llvm::FunctionType::get(llvm::Type::getInt8Ty(ctx.llvm_context), arg_types, false); // TODO: set output type and args type

            auto func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, name, ctx.llvm_module.get());

            unsigned Idx = 0;
            ctx.llvm_named_values.clear();
            for (auto &arg : func->args()) {
                auto name = this->args.get()->at(Idx++).name();
                arg.setName(name);
                ctx.llvm_named_values[name] = &arg;
            }
            llvm::BasicBlock *basic_block = llvm::BasicBlock::Create(ctx.llvm_context, "entry", func);
            ctx.llvm_builder.SetInsertPoint(basic_block);

            auto ret_val = (llvm::Value* )this->impls->codegen(ctx);
            ctx.llvm_builder.CreateRet(ret_val);

            return func;
        } else {
            // TODO: generate call function
        }
    }
}
