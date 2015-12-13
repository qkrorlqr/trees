//============================================================================
// Name        : trees.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Fuck this
//============================================================================

#include "util/progopt.h"

#include <iostream>
#include <memory>
#include <random>

using namespace std;
using namespace NUtil;

int main(int argc, const char* argv[]) {
    TProgOptions opts(argc, argv);

    if (opts.Has("t")) {
        default_random_engine gen;
        gamma_distribution<double> gamma(2, 2);
        cout << gamma(gen) << endl;

        unique_ptr<double> ptr;
    }
	return 0;
}
