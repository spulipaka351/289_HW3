#ifndef TSP_H
#define TSP_H

#include <iostream>
#include<vector>
using namespace std;

struct node {
    int a;
    int b;
    float dist;
};

void display_graph( vector<vector<float>>& dist);
void gen_graph( vector<vector<float>>& dist);
void write_file(vector<int>& path);

#endif
