#pragma once

#include "grid.h"

#include <cmath>

namespace NTrees {
    class TMse {
    public:
        template <class T>
        double Value(const T& model, const IBinarizedTrainingSet& set) const {
            double se = 0;

            for (size_t i = 0; i < set.Size(); ++i) {
                double d = set.Target(i) - model.Value(set.Features(i));
                se += d * d;
            }

            return set.Size() ? sqrt(se / set.Size()) : 0;
        }

        template <class T>
        TTargetTransform AntiGradient(const T& model, const IBinarizedTrainingSet& set) const {
            return [&model, &set](size_t i, double t) -> double {
                return t - model.Value(set.Features(i));
            };
        }
    };
}

