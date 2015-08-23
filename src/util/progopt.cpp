/*
 * progopt.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: qkrorlqr
 */

#include "progopt.h"

using namespace NUtil;

TProgOptions::TProgOptions(int argc, const char* argv[]) {
    //TODO: impl
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
