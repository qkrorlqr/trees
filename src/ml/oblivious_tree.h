#pragma once

#include "grid.h"

#include <iostream>
#include <vector>

namespace NTrees {
    struct TObliviousTree {
        std::vector<size_t> Features; //used binFeatures
        std::vector<double> Values; //bucketIdx -> bucketValue, bucketIdx=bitmask

        double Value(const TBinFeatures& binFeatures) const;
    };

    template <size_t H>
    size_t BucketIndex(const std::vector<size_t>& bf, const TBinFeatures& binFeatures);
    size_t BucketIndex(const std::vector<size_t>& bf, const TBinFeatures& binFeatures);

    void Save(const TObliviousTree& tree, std::ostream& os);
    void Load(std::istream& is, TObliviousTree* tree);
}

