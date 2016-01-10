/*
 * oblivious_tree_learner.cpp
 *
 *  Created on: Jan 9, 2016
 *      Author: qkrorlqr
 */

#include "oblivious_tree_learner.h"

#include "loss.h"

#include <limits>

namespace NTrees {
    namespace {
        struct TBucketStats {
            double Sum = 0;
            double SumSq = 0;
            size_t Size = 0;

            void Register(double t) {
                Sum += t;
                SumSq += t * t;
                ++Size;
            }

            double Mean() const {
                return Size ? Sum / Size : 0;
            }

            double Var() const {
                return Size ? SumSq / Size - Mean() * Mean() : 0;
            }

            double Score() const {
                return Size * Var();
            }
        };
    }

    namespace {
        template <size_t H>
        void SelectFeatures(const IBinarizedTrainingSet& trainingSet,
                            TObliviousTree& result,
                            std::vector<TBucketStats>& bucket2Stats)
        {
            result.Features.resize(H);
            double bestScore = std::numeric_limits<double>::max();
            size_t bestFeature = 0;

            for (size_t f = 0; f < trainingSet.FeatureCount(); ++f) {
                result.Features.back() = f;

                bucket2Stats.clear();
                bucket2Stats.resize(1 << H);

                for (size_t i = 0; i < trainingSet.Size(); ++i) {
                    bucket2Stats[BucketIndex<H>(result.Features, trainingSet.Features(i))].Register(trainingSet.Target(i));
                }

                double score = 0;
                for (const auto& bucketStat : bucket2Stats) {
                    score += bucketStat.Score();
                }

                if (score < bestScore) {
                    bestScore = score;
                    bestFeature = f;
                }
            }

            result.Features.back() = bestFeature;

            std::cerr << "height=" << H << ", feature=" << bestFeature << ", score=" << bestScore << std::endl;
        }

        template <size_t H>
        void SelectFeaturesLoop(const IBinarizedTrainingSet& trainingSet,
                         TObliviousTree& result,
                         std::vector<TBucketStats>& bucket2Stats)
        {
            SelectFeaturesLoop<H - 1>(trainingSet, result, bucket2Stats);
            SelectFeatures<H>(trainingSet, result, bucket2Stats);
        }

        template <>
        void SelectFeaturesLoop<0>(const IBinarizedTrainingSet&,
                                   TObliviousTree&,
                                   std::vector<TBucketStats>&)
        {
        }
    }

    template <size_t H>
    TObliviousTree TObliviousTreeLearner<H>::Fit() const {
        TObliviousTree result;

        std::vector<TBucketStats> bucket2Stats;

        SelectFeaturesLoop<H>(TrainingSet, result, bucket2Stats);

        result.Values.resize(1 << H);

        for (size_t bucketIndex = 0; bucketIndex < bucket2Stats.size(); ++bucketIndex) {
            result.Values[bucketIndex] = bucket2Stats[bucketIndex].Mean();
            //std::cerr << "bucket=" << bucketIndex << ", value=" << result.Values[bucketIndex] << std::endl;
        }

        if (ValidationSet) {
            std::cerr << "mse=" << TMse().Value(result, *ValidationSet) << std::endl;
        }

        return result;
    }

    template TObliviousTree TObliviousTreeLearner<6>::Fit() const;
    template TObliviousTree TObliviousTreeLearner<5>::Fit() const;
    template TObliviousTree TObliviousTreeLearner<4>::Fit() const;
    template TObliviousTree TObliviousTreeLearner<3>::Fit() const;
    template TObliviousTree TObliviousTreeLearner<2>::Fit() const;
    template TObliviousTree TObliviousTreeLearner<1>::Fit() const;
}


