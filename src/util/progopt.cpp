/*
 * progopt.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: qkrorlqr
 */

#include "progopt.h"

#include <iostream>

using namespace NUtil;

TProgOptions::TProgOptions(int argc, const char* argv[]) {
    std::string lastOption;
    for (int i = 1; i < argc; ++i) {
        std::string opt(argv[i]);

        if (opt[0] == '-') {
            lastOption = opt.substr(1);
            Data[lastOption];
        } else if (lastOption.size()) {
            Data[lastOption] = opt;
            //std::cerr << "setting " << lastOption << "=" << opt << std::endl;
            lastOption.clear();
        } else {
            UnnamedOptions.push_back(opt);
            //std::cerr << "adding unnamed option " << opt << std::endl;
        }
    }
}

const std::vector<std::string>& TProgOptions::GetUnnamedOptions() const {
    return UnnamedOptions;
}

const std::string& TProgOptions::Get(const std::string& key) const {
    auto it = Data.find(key);
    if (it == Data.end()) {
        throw TProgOptionsException("no such key: " + key);
    }
    return it->second;
}

bool TProgOptions::Has(const std::string& key) const {
    return Data.count(key);
}
