#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

using namespace std;

// --- Phase 1: Construction (Nearest Neighbor) ---
// Builds a greedy path starting at 'start'
float run_nn(const vector<vector<float > >& dist, vector<int>& path, int start) {
    int N = dist.size();
    vector<bool> visited(N, false);
    path.clear();
    path.reserve(N + 1);

    int current = start;
    visited[current] = true;
    path.push_back(current);

    float current_cost = 0.0f;

    for (int step = 1; step < N; step++) {
        float best = 1e9;
        int next = -1;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[current][j] < best) {
                best = dist[current][j];
                next = j;
            }
        }

        if (next == -1) break; 

        visited[next] = true;
        path.push_back(next);
        current_cost += best;
        current = next;
    }

    // Close the cycle
    current_cost += dist[current][start];
    path.push_back(start);
    
    return current_cost;
}

// --- Phase 2: Improvement (2-Opt) ---
// Takes an existing path and optimizes it
float run_2opt_improvement(const vector<vector<float > >& dist, vector<int>& path, float current_cost, long long &cycles) {
    int N = dist.size();
    bool improvement = true;
    
    while (improvement) {
        improvement = false;

        for (int i = 0; i < N - 2; ++i) {
            for (int k = i + 2; k < N; ++k) {
                
                int u = path[i];
                int v = path[i+1];
                int x = path[k];
                int y = path[k+1];

                float d_curr = dist[u][v] + dist[x][y];
                float d_new = dist[u][x] + dist[v][y];

                if (d_new < d_curr) {
                    reverse(path.begin() + i + 1, path.begin() + k + 1);
                    current_cost -= (d_curr - d_new);
                    improvement = true;
                }
            }
        }
    }
    
    cycles++; // Count this optimization pass
    return current_cost;
}

// --- Wrapper for Backward Compatibility ---
// Does BOTH construction and improvement (Slow if called in a loop)
float two_opt(const vector<vector<float > >& dist,
              vector<int>& path,
              int start,
              long long &cycles)
{
    float cost = run_nn(dist, path, start);
    return run_2opt_improvement(dist, path, cost, cycles);
}