/*
 * training_set.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: qkrorlqr
 */

#include "training_set.h"

#include <cstdlib>
#include <sstream>
#include <string>

using namespace NTrees;

TTrainingSet::TTrainingSet(std::istream& is) {
    std::string line;

    while (std::getline(is, line)) {
        std::istringstream ss(line);

        Records.push_back({});
        TRecord& record = Records.back();

        std::string field;

        std::getline(ss, field, '\t');
        record.ReqID = atol(field.c_str());

        std::getline(ss, field, '\t');
        record.Target = atof(field.c_str());

        std::getline(ss, field, '\t');
        std::getline(ss, field, '\t');

        record.Features.reserve(FeatureCount);

        while (std::getline(ss, field, '\t')) {
            record.Features.push_back(atof(field.c_str()));
        }

        if (!FeatureCount) {
            FeatureCount = record.Features.size();
        } else if (FeatureCount != record.Features.size()) {
            throw TTrainingSetFormatException() << "different feature counts, error on line\t" << line;
        }
    }
}
