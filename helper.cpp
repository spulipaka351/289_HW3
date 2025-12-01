#include "helper.h"
#include <fstream>
#include <sstream>
#include <string>
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
