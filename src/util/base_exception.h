#pragma once

#include <string>

class TBaseException: public std::exception {
private:
    std::string S;

public:
    TBaseException() {}
    TBaseException(const std::string& s) : S(s) {}

public:
    const char* what() const noexcept override {
        return S.c_str();
    }

    TBaseException& operator<<(const std::string& s) {
        S += s;
        return *this;
    }

    TBaseException& operator<<(const char* s) {
        S += s;
        return *this;
    }

    template <class T>
    TBaseException& operator<<(const T& t) {
        S += std::to_string(t);
        return *this;
    }
};


