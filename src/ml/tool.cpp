/*
 * tool.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: qkrorlqr
 */

#include "tool.h"

using namespace NTrees;

void NTrees::Print(const ITrainingSet& ts, std::ostream& os) {
    for (size_t i = 0; i < ts.Size(); ++i) {
        auto& rec = ts[i];
        os << rec.ReqID << '\t' << rec.Target << "\tfoo\tfoo";

        for (size_t j = 0; j < ts.GetFeatureCount(); ++j) {
            os << '\t' << rec.Features[j];
        }

        os << std::endl;
    }
}


