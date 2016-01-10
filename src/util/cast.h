#pragma once

#include <string>

template <class T>
T FromString(const std::string& s) {
    return std::stol(s);
}

template <>
inline double FromString(const std::string& s) {
    return std::stod(s);
}
