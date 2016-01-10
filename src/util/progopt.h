#pragma once

#include "base_exception.h"
#include "cast.h"

#include <unordered_map>
#include <vector>

namespace NUtil {
    class TProgOptions {
    private:
        std::unordered_map<std::string, std::string> Data;
        std::vector<std::string> UnnamedOptions;

    public:
        TProgOptions(int argc, const char* argv[]);

    public:
        const std::vector<std::string>& GetUnnamedOptions() const;
        const std::string& Get(const std::string& k) const;
        bool Has(const std::string& k) const;

        template <class T>
        T Get(const std::string& k, T def) const {
            auto it = Data.find(k);

            if (it == Data.end()) {
                return def;
            }

            return FromString<T>(it->second);
        }
    };

    class TProgOptionsException: public TBaseException {
    public:
        TProgOptionsException(const std::string& s) : TBaseException(s) {}
    };
}

