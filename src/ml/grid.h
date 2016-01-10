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

    TBinFeatures BinarizeFeatures(const TGrid& grid, const TFeatures& features);

    class IBinarizedTrainingSet {
    public:
        virtual ~IBinarizedTrainingSet() {}

        virtual size_t Size() const = 0;
        virtual const TBinFeatures& Features(size_t i) const = 0;
        virtual double Target(size_t i) const = 0;
        virtual size_t FeatureCount() const = 0;
    };

    class TBinarizedTrainingSetImpl: public IBinarizedTrainingSet {
    private:
        std::vector<TBinFeatures> Features_;
        std::vector<double> Target_;

    public:
        TBinarizedTrainingSetImpl(const ITrainingSet& ts, const TGrid& grid);

    public:
        size_t Size() const override {
            return Features_.size();
        }

        const TBinFeatures& Features(size_t i) const override {
            return Features_[i];
        }

        double Target(size_t i) const override {
            return Target_[i];
        }

        size_t FeatureCount() const override {
            return Features_.size() ? Features_.front().size() : 0;
        }
    };

    using TTargetTransform = std::function<double(size_t, double)>;

    class TBinarizedTrainingSetRemap: public IBinarizedTrainingSet {
    private:
        const IBinarizedTrainingSet& Parent;
        TRemap Remap;
        TTargetTransform TargetTransform;

    public:
        TBinarizedTrainingSetRemap(const IBinarizedTrainingSet& parent,
                                   const TRemap& remap,
                                   const TTargetTransform& targetTransform)
            : Parent(parent)
            , Remap(remap)
            , TargetTransform(targetTransform)
        {}

    public:
        const TBinFeatures& Features(size_t i) const override {
            return Parent.Features(Remap(i));
        }

        double Target(size_t i) const override {
            return TargetTransform(Remap(i), Parent.Target(Remap(i)));
        }

        size_t Size() const override {
            return Parent.Size();
        }

        size_t FeatureCount() const override {
            return Parent.FeatureCount();
        }
    };
}


