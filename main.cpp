#include <iostream>
#include <vector>
#include <chrono>
#include "helper.h"
#include "tsp.h"   // <-- NOT astar.h

using namespace std;

int main() {
    int N = 1000;
    vector<vector<float>> graph(N, vector<float>(N, 1e9f));
    gen_graph(graph);

    long long cycles = 0;
    float best_cost = 1e18;
    vector<int> best_path, temp_path;

    auto start = chrono::high_resolution_clock::now();

    // Phase-2: Run NN from each node
    for (int s = 0; s < N; s++) {
        float cost = tsp_nn(graph, temp_path, s, cycles);
        if (cost < best_cost) {
            best_cost = cost;
            best_path = temp_path;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> runtime = end - start;

    cout << "PHASE-2 RESULTS" << endl;
    cout << "Best NN cost: " << best_cost << endl;
    cout << "Cycles evaluated: " << cycles << endl;
    cout << "Runtime: " << runtime.count() << " seconds" << endl;

    cout << "First 15 nodes: ";
    for (int i = 0; i < 15; i++)
        cout << best_path[i] << " ";
    cout << "..." << endl;
    write_file(best_path);
    return 0;
}
