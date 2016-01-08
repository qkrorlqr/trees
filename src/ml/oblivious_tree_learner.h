#pragma once

#include "grid.h"
#include "oblivious_tree.h"

namespace NTrees {
    class TObliviousTreeLearner {
    private:
        const IBinarizedTrainingSet& TrainingSet;

    public:
        TObliviousTreeLearner(const IBinarizedTrainingSet& trainingSet)
            : TrainingSet(trainingSet)
        {}

    public:
        TObliviousTree Fit(size_t height = 6) const;
    };
}

