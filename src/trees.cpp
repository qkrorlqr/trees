//============================================================================
// Name        : trees.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Fuck this
//============================================================================

#include <ml/boosting.h>
#include <ml/grid.h>
#include <ml/loss.h>
#include <ml/oblivious_tree_learner.h>
#include <ml/tool.h>
#include <ml/training_set.h>

#include <util/progopt.h>
#include <util/saveload.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <random>

using namespace std;
using namespace NTrees;
using namespace NUtil;

int main(int argc, const char* argv[]) {
    TProgOptions opts(argc, argv);

    std::ifstream fsl(opts.Get("f"));
    TTrainingSet learn(fsl);
    std::ifstream fst(opts.Get("t"));
    TTrainingSet validation(fst);

    cout << learn.Size() << endl;
    cout << learn.GetFeatureCount() << endl;

    TGrid grid = BuildGrid(learn);

    TBinarizedTrainingSetImpl binarizedLearn(learn, grid);
    TBinarizedTrainingSetImpl binarizedValidation(validation, grid);

    cout << binarizedLearn.FeatureCount() << endl;

    TBoostedLearner<TObliviousTreeLearner<>, TMse> learner(binarizedLearn, opts.Get("a", 0.01), opts.Get("i", 100));
    learner.SetValidationSet(binarizedValidation);

    auto model = learner.Fit();

    {
        std::ofstream ofs(opts.Get("o"), std::ios_base::out | std::ios_base::binary);
        Save(model, ofs);
    }

    /*
    TObliviousTreeLearner learner(binarizedLearn);
    learner.SetValidationSet(binarizedValidation);

    TObliviousTree tree = learner.Fit();

    {
        std::ofstream ofs(opts.Get("o"), std::ios_base::out | std::ios_base::binary);
        Save(tree, ofs);
    }
    */

    /*
    TObliviousTree tree2;

    {
        std::ifstream ifs(opts.Get("o"), std::ios_base::in | std::ios_base::binary);
        Load(ifs, &tree2);
    }

    cout << tree.Features.size() << endl;
    cout << tree.Values.size() << endl;
    cout << tree2.Features.size() << endl;
    cout << tree2.Values.size() << endl;
    cout << (tree.Features == tree2.Features) << endl;
    cout << (tree.Values == tree2.Values) << endl;
    */

    /*
    {
        std::ofstream ofs(opts.Get("o"), std::ios_base::out | std::ios_base::binary);
        Save(grid, ofs);
    }

    TGrid grid2;

    {
        std::ifstream ifs(opts.Get("o"), std::ios_base::in | std::ios_base::binary);
        Load(ifs, &grid2);
    }

    cout << grid.Intervals.size() << endl;
    cout << grid2.Intervals.size() << endl;
    cout << (grid.Intervals == grid2.Intervals) << endl;
    */

    if (opts.Has("p")) {
        Print(learn, cout);
    }

    if (opts.Has("t")) {
        cout << sizeof(long long) << endl;
        cout << sizeof(long) << endl;
        cout << sizeof(int) << endl;

        default_random_engine gen;
        gamma_distribution<double> gamma(2, 2);
        cout << gamma(gen) << endl;

        unique_ptr<double> ptr;
    }
	return 0;
}
