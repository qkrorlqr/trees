#pragma once

#include <util/base_exception.h>

#include <functional>
#include <iostream>
#include <string>
//#include <unordered_set>
#include <vector>

namespace NTrees {
    using TFeatures = std::vector<double>;
    //using TBinFeatures = std::unordered_set<size_t>;
    using TBinFeatures = std::vector<bool>;

    struct TRecord {
        long ReqID;
        double Target;
        TFeatures Features;
    };

    using TRemap = std::function<size_t(size_t)>;

    class ITrainingSet {
    public:
        virtual ~ITrainingSet() {}

    public:
        virtual size_t Size() const = 0;
        virtual size_t GetFeatureCount() const = 0;
        virtual const TRecord& operator[](size_t i) const = 0;
    };

    class TTrainingSetView: public ITrainingSet {
    private:
        const ITrainingSet& Parent;
        TRemap Remap;

    public:
        TTrainingSetView(const ITrainingSet& set, const TRemap& remap)
            : Parent(set)
            , Remap(remap)
        {}

    public:
        size_t Size() const override {
            return Parent.Size();
        }

        const TRecord& operator[](size_t i) const override {
            return Parent[Remap(i)];
        }

        size_t GetFeatureCount() const override {
            return Parent.GetFeatureCount();
        }
    };

    class TTrainingSet: public ITrainingSet {
    private:
        std::vector<TRecord> Records;
        size_t FeatureCount = 0;

    public:
        TTrainingSet(std::istream& is);

    public:
        size_t Size() const override {
            return Records.size();
        }

        const TRecord& operator[](size_t i) const override {
            return Records[i];
        }

        TTrainingSetView GetView(const TRemap& remap) const {
            return TTrainingSetView(*this, remap);
        }

        size_t GetFeatureCount() const override {
            return FeatureCount;
        }
    };

    class TTrainingSetFormatException: public TBaseException {};
}


