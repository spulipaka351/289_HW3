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
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

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

