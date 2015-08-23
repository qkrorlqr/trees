#pragma once

#include "base_exception.h"

#include <unordered_map>

namespace NUtil {
    class TProgOptions {
    private:
        std::unordered_map<std::string, std::string> Data;

    public:
        TProgOptions(int argc, const char* argv[]);

    public:
        const std::string& Get(const std::string& k) const;
        bool Has(const std::string& k) const;
    };

    class TProgOptionsException : public TBaseException {
    public:
        TProgOptionsException(const std::string& s) : TBaseException(s) {}
    };
}

