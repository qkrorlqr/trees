/*
 * oblivious_tree.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: qkrorlqr
 */

#include "oblivious_tree.h"

#include <util/saveload.h>

namespace NTrees {
    double TObliviousTree::Value(const TBinFeatures& binFeatures) const {
        size_t index = 0;

        for (size_t i = 0; i < Features.size(); i++) {
            index += uint32_t(binFeatures[Features[i]]) << i;
        }

        return Values[index];
    }

    void Save(const TObliviousTree& tree, std::ostream& os) {
        Save(tree.Features, os);
        Save(tree.Values, os);
    }

    void Load(std::istream& is, TObliviousTree* tree) {
        Load(is, &tree->Features);
        Load(is, &tree->Values);
    }
}



