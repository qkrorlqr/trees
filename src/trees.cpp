//============================================================================
// Name        : trees.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Fuck this
//============================================================================

#include <iostream>
#include <memory>
#include <random>

using namespace std;

int main() {
	default_random_engine gen;
	gamma_distribution<double> gamma(2, 2);
	cout << gamma(gen) << endl;

	unique_ptr<double> ptr;
	return 0;
}
