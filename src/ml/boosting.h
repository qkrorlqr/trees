#pragma once

#include "grid.h"

#include <util/containers.h>
#include <util/saveload.h>

#include <random>
#include <unordered_map>
#include <vector>

namespace NTrees {
    template <class T>
    struct TSimpleValueGetter {
        const std::vector<T>& Weaks;

        TSimpleValueGetter(const std::vector<T>& weaks)
            : Weaks(weaks)
        {}

        double Value(size_t i, const TBinFeatures& binFeatures) const {
            return Weaks[i].Value(binFeatures);
        }
    };

    template <class T>
    struct TCachingValueGetter: public TSimpleValueGetter<T> {
        using TKey = std::pair<size_t, intptr_t>;
        mutable std::unordered_map<TKey, double, TPairHash<size_t, intptr_t>> Cache;

        using TSimpleValueGetter<T>::TSimpleValueGetter;

        double Value(size_t i, const TBinFeatures& binFeatures) const {
            double& v = Cache[TKey(i, intptr_t(&binFeatures))];

            if (!v) {
                v = this->Weaks[i].Value(binFeatures);
            }

            return v;
        }
    };

    template <class T, template<class> class V = TSimpleValueGetter>
    struct TBoostedModel {
        std::vector<T> Weaks;
        double Alpha;
        V<T> ValueGetter;

        TBoostedModel(double alpha)
            : Alpha(alpha)
            , ValueGetter(Weaks)
        {}

        double Value(const TBinFeatures& binFeatures) const {
            double v = 0;
            for (size_t i = 0; i < Weaks.size(); ++i) {
                v += Alpha * ValueGetter.Value(i, binFeatures);
            }

            return v;
        }
    };

    template <class T, template<class> class V>
    void Save(const TBoostedModel<T, V>& model, std::ostream& os) {
        Save(model.Alpha, os);
        Save(model.Weaks, os);
    }

    template <class T, template<class> class V>
    void Load(std::istream& is, TBoostedModel<T, V>* model) {
        Load(is, &model->Alpha);
        Load(is, &model->Weaks);
    }

    template <class T, class L>
    class TBoostedLearner {
    public:
        using TModel = TBoostedModel<typename T::TModel, TCachingValueGetter>;
        //using TModel = TBoostedModel<typename T::TModel>;

    private:
        const IBinarizedTrainingSet& Learn;
        const IBinarizedTrainingSet* Validation;
        double Alpha;
        size_t Iters;

    public:
        TBoostedLearner(const IBinarizedTrainingSet& learn, double alpha, size_t iters)
            : Learn(learn)
            , Validation(nullptr)
            , Alpha(alpha)
            , Iters(iters)
        {}

    public:
        void SetValidationSet(const IBinarizedTrainingSet& validationSet) {
            Validation = &validationSet;
        }

        TModel Fit() const {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, Learn.Size() - 1);

            L loss;
            TModel model(Alpha);

            for (size_t i = 0; i < Iters; ++i) {
                std::cerr << "iter=" << i << std::endl;

                std::vector<size_t> remap(Learn.Size());
                for (size_t j = 0; j < Learn.Size(); ++j) {
                    remap[j] = dis(gen);
                }

                TBinarizedTrainingSetRemap remappedLearn(
                    Learn,
                    [&remap](size_t idx) -> size_t {
                        return remap[idx];
                    },
                    loss.AntiGradient(model, Learn)
                );
                T weakLearner(remappedLearn);

                if (Validation) {
                    weakLearner.SetValidationSet(*Validation);
                }

                model.Weaks.push_back(weakLearner.Fit());

                ReportLoss(i, "learn", loss, model, Learn);
                if (Validation) {
                    ReportLoss(i, "validation", loss, model, *Validation);
                }
            }

            return model;
        }

    private:
        void ReportLoss(size_t iter,
                        const std::string& tag,
                        const L& loss,
                        const TModel& model,
                        const IBinarizedTrainingSet& s) const
        {
            std::cerr << "iter=" << iter << ", loss(" << tag << ")=" << loss.Value(model, s) << std::endl;
        }
    };
}

