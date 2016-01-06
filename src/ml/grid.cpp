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
}


