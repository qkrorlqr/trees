#pragma once

#include <util/base_exception.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace NTrees {
    struct TRecord {
        long ReqID;
        double Target;
        std::vector<double> Features;
    };

    using TRemap = std::function<unsigned(unsigned)>;

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


