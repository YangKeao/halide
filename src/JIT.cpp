//
// Created by yangkeao on 6/14/19.
//

#include "JIT.h"

namespace Halide {
    void JIT::map_var(std::string name, uint64_t addr)  {
        engine->addGlobalMapping(name, addr);
    }
}
