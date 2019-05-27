//
// Created by yangkeao on 5/27/19.
//

#ifndef HALIDE_UTIL_H
#define HALIDE_UTIL_H

#include <string>

namespace Halide {
    namespace Internal {
        std::string make_entity_name(char prefix);
        std::string make_entity_name(std::string prefix);
        int unique_count(size_t h);
    }
}

#endif //HALIDE_UTIL_H
