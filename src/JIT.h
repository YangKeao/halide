//
// Created by yangkeao on 6/14/19.
//

#ifndef HALIDE_JIT_H
#define HALIDE_JIT_H

#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"

namespace Halide {
    class JIT {
      private:
        llvm::ExecutionEngine* engine;
        llvm::RTDyldMemoryManager* memory_manager;
      public:
        JIT(std::unique_ptr<llvm::Module> module) {
            memory_manager = new llvm::SectionMemoryManager();
            engine = llvm::EngineBuilder(std::move(module)).setEngineKind(llvm::EngineKind::JIT)
                    .setVerifyModules(true)
                    .setMCJITMemoryManager(std::unique_ptr<llvm::RTDyldMemoryManager>(memory_manager))
                    .setOptLevel(llvm::CodeGenOpt::Default)
                    .create();
        }
    };
}


#endif //HALIDE_JIT_H
