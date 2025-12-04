#include <iostream>
#include <vector>
#include <chrono>
#include "helper.h"
#include "tsp.h"   
#include "2-opt.h"
using namespace std;

int main(int argc, char* argv[]) {
    // 1. Check Arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // 2. Read File
    string filename = argv[1];
    // int ch = stoi(argv[2]);
    int N = 1000;
    vector<vector<float > > graph(N, vector<float>(N, 1e9f));
    gen_graph(graph,filename);

    long long cycles = 0;
    float best_cost = 1e18;
    vector<int> best_path, temp_path;
    chrono::duration<double> runtime;
    auto start = chrono::high_resolution_clock::now();
        //NAIVE
        // cout<<"naive"<<endl;
        // for (int s = 0; s < N; s++) {
        //     float cost = tsp_nn(graph, temp_path, s, cycles);
        //     if (cost < best_cost) {
        //         best_cost = cost;
        //         best_path = temp_path;
        //     }
        // }
        // auto endtime =chrono::high_resolution_clock::now();
        // runtime = endtime - start;


    

        cout << "Phase 1: Finding best NN start node..." << endl;
        for (int s = 0; s < N; s++) {
            // Only run the NN construction (Fast)
            float cost = run_nn(graph, temp_path, s);
            
            if (cost < best_cost) {
                best_cost = cost;
                best_path = temp_path;
            }
        }
    
        // 2. Run SLOW 2-Opt only ONCE on the winner
        cout << "Phase 2: Optimizing best NN path..." << endl;
        best_cost = run_2opt_improvement(graph, best_path, best_cost, cycles);
    
        auto end = chrono::high_resolution_clock::now();
         runtime = end - start;
   
    

    cout << "PHASE-2 RESULTS" << endl;
    cout << "Best NN cost: " << best_cost << endl;
    cout << "Cycles evaluated: " << int_to_scientific(cycles )<< endl;
    cout << "Runtime: " << runtime.count() << " seconds" << endl;
    
    cout << "First 15 nodes: ";
    for (int i = 0; i < 15; i++)
        cout << best_path[i] << " ";
    cout << "..." << endl;
    write_file(best_path,filename);
    return 0;
}
