#pragma once

#include <unordered_map>

template <class T, typename U>
struct TPairHash {
    size_t operator()(const std::pair<T, U> &key) const {
        return std::hash<T>()(key.first) ^ std::hash<U>()(key.second);
    }
};

