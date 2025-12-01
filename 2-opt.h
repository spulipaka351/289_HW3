#ifndef OPT_H
#define OPT_H

#include <vector>
#include <utility> // Required for std::pair
using namespace std;
// Function declarations using std:: prefix
// Note: We use std::vector and std::pair because 'using namespace std' 
// is bad practice in header files (it forces it on every file that includes this).


float run_nn(const vector<vector<float > >& dist, vector<int>& path, int start) ;
float run_2opt_improvement(const vector<vector<float > >& dist, vector<int>& path, float current_cost, long long &cycles);

float two_opt(const vector<vector<float > >& dist,
    vector<int>& path,
    int start,
    long long &cycles);

#endif