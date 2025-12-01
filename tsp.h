#ifndef Astar
#define Astar
#include <iostream>
#include <vector>
#include "helper.h"
using namespace std;

float TSP(const vector<vector<float>>& dist);

float tsp_nn(const vector<vector<float>>& dist,
             vector<int>& path,
             int start,
             long long &cycles);



#endif