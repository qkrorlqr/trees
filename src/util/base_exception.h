#pragma once

#include <string>

class TBaseException : public std::exception {
private:
    std::string S;

public:
    TBaseException(const std::string& s) : S(s) {}

public:
    const char* what() const noexcept override {
        return S.c_str();
    }
};


