//============================================================================
// Name        : trees.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Fuck this
//============================================================================

#include <ml/grid.h>
#include <ml/training_set.h>
#include <ml/tool.h>
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

    std::ifstream fs(opts.Get("i"));
    TTrainingSet learn(fs);

    cout << learn.Size() << endl;
    cout << learn.GetFeatureCount() << endl;

    TGrid grid = BuildGrid(learn);

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
