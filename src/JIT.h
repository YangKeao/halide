//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_JIT_H
#define HALIDE_JIT_H

#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "Buffer.h"

#include <iostream>

namespace Halide {
    class JIT {
      private:
        llvm::ExecutionEngine* engine;
        llvm::RTDyldMemoryManager* memory_manager;
      public:
        JIT(std::unique_ptr<llvm::Module> module) {
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();

            memory_manager = new llvm::SectionMemoryManager();
            std::string err_str;
            engine = llvm::EngineBuilder(std::move(module)).setEngineKind(llvm::EngineKind::JIT)
                    .setVerifyModules(true)
                    .setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(memory_manager))
                    .setOptLevel(llvm::CodeGenOpt::Default)
                    .setErrorStr(&err_str)
                    .create();

            if (!engine) {
                std::cerr << err_str;
            }
        }

        void map_var(std::string name, uint64_t addr);

        void run() {
            auto (*fptr)() = (void(*)())engine->getFunctionAddress("__call_point__");
            fptr();
        }
    };
}


#endif //HALIDE_JIT_H
