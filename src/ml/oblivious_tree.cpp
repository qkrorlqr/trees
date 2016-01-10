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
        return Values[BucketIndex(Features, binFeatures)];
    }

    namespace {
        template <size_t I>
        void BucketIndex(const std::vector<size_t>& bf, const TBinFeatures& binFeatures, size_t& index) {
            index += uint32_t(binFeatures[bf[I - 1]]) << (I - 1);
        }

        template <size_t I>
        void BucketIndexLoop(const std::vector<size_t>& bf, const TBinFeatures& binFeatures, size_t& index) {
            BucketIndexLoop<I - 1>(bf, binFeatures, index);
            BucketIndex<I>(bf, binFeatures, index);
        }

        template <>
        void BucketIndexLoop<0>(const std::vector<size_t>&, const TBinFeatures&, size_t&) {
        }
    }

    template <size_t H>
    size_t BucketIndex(const std::vector<size_t>& bf, const TBinFeatures& binFeatures) {
        size_t index = 0;
        BucketIndexLoop<H>(bf, binFeatures, index);
        return index;
    }

    size_t BucketIndex(const std::vector<size_t>& bf, const TBinFeatures& binFeatures) {
        size_t index = 0;

        for (size_t i = 0; i < bf.size(); i++) {
            index += uint32_t(binFeatures[bf[i]]) << i;
        }

        return index;
    }

    void Save(const TObliviousTree& tree, std::ostream& os) {
        Save(tree.Features, os);
        Save(tree.Values, os);
    }

    void Load(std::istream& is, TObliviousTree* tree) {
        Load(is, &tree->Features);
        Load(is, &tree->Values);
    }

    template size_t BucketIndex<6>(const std::vector<size_t>&, const TBinFeatures&);
    template size_t BucketIndex<5>(const std::vector<size_t>&, const TBinFeatures&);
    template size_t BucketIndex<4>(const std::vector<size_t>&, const TBinFeatures&);
    template size_t BucketIndex<3>(const std::vector<size_t>&, const TBinFeatures&);
    template size_t BucketIndex<2>(const std::vector<size_t>&, const TBinFeatures&);
    template size_t BucketIndex<1>(const std::vector<size_t>&, const TBinFeatures&);
}



