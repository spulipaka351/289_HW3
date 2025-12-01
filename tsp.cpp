#include <iostream>
#include "tsp.h"

#include <vector>
#include <limits>
#include <iostream>
#include <cmath>
using namespace std;

float TSP(const vector<vector<float>>& dist) {
    int N = dist.size();
    
    vector<bool> visited(N, false);
    vector<int> path;
    path.reserve(N);

    int current = 0; // start at node 0
    visited[current] = true;
    path.push_back(current);

    float total_cost = 0.0f;

    for (int step = 1; step < N; step++) {
        float best = 1e9;
        int next = -1;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[current][j] < best) {
                best = dist[current][j];
                next = j;
            }
        }

        if (next == -1) {
            cout << "No unvisited nodes found — Graph might be disconnected!\n";
            break;
        }

        visited[next] = true;
        path.push_back(next);
        total_cost += best;
        current = next;
    }

    // Return back to start to complete tour
    total_cost += dist[current][0];
    path.push_back(0);

    cout << "TSP Approx Path (first 15 nodes): ";
    for (int i = 0; i < min((int)path.size(), 15); i++)
        cout << path[i] << " ";
    cout << "...\n";

    return total_cost;
}
#include <vector>
#include <limits>
using namespace std;

float tsp_nn(const vector<vector<float>>& dist,
             vector<int>& path,
             int start,
             long long &cycles)
{
    int N = dist.size();
    vector<bool> visited(N, false);
    path.clear();
    path.reserve(N + 1);

    int current = start;
    visited[current] = true;
    path.push_back(current);

    float total_cost = 0.0f;

    for (int step = 1; step < N; step++) {
        float best = 1e9;
        int next = -1;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[current][j] < best) {
                best = dist[current][j];
                next = j;
            }
        }

        visited[next] = true;
        path.push_back(next);
        total_cost += best;
        current = next;
    }

    // Close the cycle
    total_cost += dist[current][start];
    path.push_back(start);

    cycles++; // Count this full cycle

    return total_cost;
}
