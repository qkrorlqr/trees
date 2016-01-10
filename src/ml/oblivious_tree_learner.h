#pragma once

#include "grid.h"
#include "oblivious_tree.h"

namespace NTrees {
    template <size_t H = 6>
    class TObliviousTreeLearner {
    public:
        using TModel = TObliviousTree;

    private:
        const IBinarizedTrainingSet& TrainingSet;
        const IBinarizedTrainingSet* ValidationSet;

    public:
        TObliviousTreeLearner(const IBinarizedTrainingSet& trainingSet)
            : TrainingSet(trainingSet)
            , ValidationSet(nullptr)
        {}

    public:
        TObliviousTree Fit() const;

        void SetValidationSet(const IBinarizedTrainingSet& validationSet) {
            ValidationSet = &validationSet;
        }
    };
}

