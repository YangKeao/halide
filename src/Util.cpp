//
// Created by yangkeao on 5/27/19.
//

#include "Util.h"
#include <atomic>

namespace Halide {
    std::string Internal::make_entity_name(char prefix)  {
        return prefix + std::to_string(unique_count((size_t)(prefix)));
    }

    std::string Internal::make_entity_name(std::string prefix)  {
        return prefix + std::to_string(unique_count(std::hash<std::string>()((prefix))));
    }

    const int num_unique_name_counters = (1 << 14);

    std::atomic<int> unique_name_counters[num_unique_name_counters] = {};

    int Internal::unique_count(size_t h) {
        h = h & (num_unique_name_counters - 1);
        return unique_name_counters[h]++;
    }
}

