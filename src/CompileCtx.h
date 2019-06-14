//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_COMPILECTX_H
#define HALIDE_COMPILECTX_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <map>

namespace Halide {
    class CompileCtx {
      public:
        llvm::LLVMContext llvm_context;
        llvm::IRBuilder<> llvm_builder;
        std::unique_ptr<llvm::Module> llvm_module;
        std::map<std::string, llvm::Value *> llvm_named_values;

        CompileCtx(): llvm_context(), llvm_builder(this->llvm_context), llvm_module(llvm::make_unique<llvm::Module>("main_module", this->llvm_context)), llvm_named_values() {}
    };
}


#endif //HALIDE_COMPILECTX_H
