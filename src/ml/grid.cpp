/*
 * grid.cpp
 *
 *  Created on: Jan 5, 2016
 *      Author: qkrorlqr
 */

#include "grid.h"

#include <util/saveload.h>

#include <algorithm>
#include <limits>

namespace NTrees {
    TGrid BuildGrid(const ITrainingSet& ts) {
        std::vector<std::vector<double>> inverse(ts.GetFeatureCount());

        for (size_t i = 0; i < ts.Size(); ++i) {
            auto& rec = ts[i];

            for (size_t f = 0; f < ts.GetFeatureCount(); ++f) {
                inverse[f].push_back(rec.Features[f]);
            }
        }

        TGrid grid;
        grid.Intervals.resize(inverse.size());

        for (size_t f = 0; f < inverse.size(); ++f) {
            auto& x = inverse[f];
            std::sort(x.begin(), x.end());

            /*
            double step = (x.back() - x.front()) / 15;
            for (double v = x.front(); v < x.back(); v += step) {

            }
            */

            for (size_t bucket = 0; bucket < 31; ++bucket) {
                grid.Intervals[f].push_back(x[bucket * x.size() / 31]);
            }

            grid.Intervals[f].push_back(std::numeric_limits<double>::max());
        }

        return grid;
    }

    void Save(const TGrid& grid, std::ostream& os) {
        Save(grid.Intervals, os);
    }

    void Load(std::istream& is, TGrid* grid) {
        Load(is, &grid->Intervals);
    }

    TBinFeatures BinarizeFeatures(const TGrid& grid, const TFeatures& features) {
        if (grid.Intervals.size() != features.size()) {
            throw TBaseException() << "feature and interval count mismatch: " << features.size() << " != " << grid.Intervals.size();
        }

        TBinFeatures binFeatures;
        binFeatures.reserve(grid.Intervals.front().size() * grid.Intervals.size());

        for (size_t f = 0; f < features.size(); ++f) {
            bool found = false;

            for (size_t bf = 0; bf < grid.Intervals[f].size(); ++bf) {
                double right = grid.Intervals[f][bf];

                if (!found && features[f] < right) {
                    binFeatures.push_back(true);
                } else {
                    binFeatures.push_back(false);
                }
            }
        }

        return binFeatures;
    }

    TBinarizedTrainingSetImpl::TBinarizedTrainingSetImpl(const ITrainingSet& ts, const TGrid& grid) {
        Features_.reserve(ts.Size());
        Target_.reserve(ts.Size());

        for (size_t i = 0; i < ts.Size(); ++i) {
            Features_.push_back(BinarizeFeatures(grid, ts[i].Features));
            Target_.push_back(ts[i].Target);
        }
    }
}


