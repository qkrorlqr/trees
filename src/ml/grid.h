#pragma once

#include "training_set.h"

#include <iostream>
#include <vector>

namespace NTrees {
    using TIntervals = std::vector<double>;

    struct TGrid {
        std::vector<TIntervals> Intervals;
    };

    TGrid BuildGrid(const ITrainingSet& ts);
    void Save(const TGrid& grid, std::ostream& os);
    void Load(std::istream& is, TGrid* grid);
}


