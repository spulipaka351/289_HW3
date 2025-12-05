#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

using namespace std;
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
                    cycles++;
                }
            }
        }
    }
    
     // Count this optimization pass
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
void display_graph( vector<vector<float > >& dist) {
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < dist[i].size(); j++) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}


void gen_graph(vector<vector<float > >& dist, string filename) {
    string line;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "file not uploaded" << endl;
        return;
    }

    // Skip first 2 lines
    getline(file, line);
    getline(file, line);

    int a, b;
    float d;

    while (file >> a >> b >> d) {
        a--; // convert to 0-index
        b--;

        dist[a][b] = d;
        dist[b][a] = d; // undirected graph
    }

    file.close();
}


void write_file( vector<int>& path, string filename) {
    string output_file = "path_"+ filename;
    fstream file(output_file, ios::out); // No "./" needed usually

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

   
    for (int p : path) {
        file << p << ",";
    }
    file << endl;
    
    file.close();
}

string int_to_scientific(int number) {
    // 1. Create a stringstream object
    stringstream ss;

    // 2. Apply manipulators:
    //    - scientific: forces the output to be in scientific notation (e.g., 1.000000e+02)
    //    - setprecision(0): sets the number of digits *after* the decimal point to 0.
    //      This is a key step to get '1e+02' instead of '1.000000e+02'.
    ss << scientific << setprecision(0) << number;

    // 3. Get the resulting string
    string result = ss.str();

    // 4. Post-process the string to match the exact "1e2" format:
    //    a) Remove the '+' sign if present (e.g., "1e+02" -> "1e02")
    size_t plus_pos = result.find('+');
    if (plus_pos != string::npos) {
        result.erase(plus_pos, 1);
    }
    
    //    b) Remove the leading '0' from the exponent if present (e.g., "1e02" -> "1e2")
    //       This works for exponents < 100.
    size_t e_pos = result.find('e');
    if (e_pos != string::npos && result.length() > e_pos + 2 && result[e_pos + 1] == '0') {
        result.erase(e_pos + 1, 1);
    }

    //    c) Remove the decimal point and trailing zeros (e.g., "1.e2" -> "1e2")
    size_t dot_pos = result.find('.');
    if (dot_pos != string::npos) {
        // Find where the 'e' starts
        size_t e_start = result.find('e');
        
        // Erase everything from the dot up to, but not including, 'e'
        if (e_start != string::npos && e_start > dot_pos) {
            result.erase(dot_pos, e_start - dot_pos);
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
    // 1. Check Arguments
    
    // 2. Read File
    
    // int ch = stoi(argv[2]);
    int N = 1000;
    vector<vector<float > > graph(N, vector<float>(N, 1e9f));
    gen_graph(graph,"TSP_1000_euclidianDistance.txt");

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
    write_file(best_path,"euclidean.txt");
    return 0;
}
