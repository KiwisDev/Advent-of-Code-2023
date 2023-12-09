#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

bool isAllZero(vector<int>* vec);

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string line;

    int sum = 0;

    while (getline(file, line)) {
        vector<vector<int>> sequences;
        vector<int> tmp;

        istringstream ss(line);
        string buff;

        while (ss >> buff) {    // Read data
            tmp.push_back(stoi(buff));
        }
        sequences.push_back(tmp);
        tmp.clear();

        while (!isAllZero(&sequences[sequences.size() - 1])) {  // Generate all sequences
            for (int i = 1; i < sequences[sequences.size() - 1].size(); i++) {
                tmp.push_back(sequences[sequences.size() - 1][i] - sequences[sequences.size() - 1][i - 1]);
            }
            sequences.push_back(tmp);
            tmp.clear();
        }

        sequences[sequences.size() - 1].push_back(0);   // Add '0' to last sequences

        for (int i = sequences.size() - 2; i >= 0; i--) {   // Extrapolate values
            sequences[i].push_back(sequences[i][sequences[i].size() - 1] + sequences[i + 1][sequences[i + 1].size() - 1]);
        }

        sum += sequences[0][sequences[0].size() - 1];

        // -- Print extrapolated sequences -- //
        /*for (int y = 0; y < sequences.size(); y++) {
            for (int x = 0; x < sequences[y].size(); x++) {
                cout << sequences[y][x] << " ";
            }
            cout << endl;
        }

        cout << endl;*/
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(endChrono - startChrono);

    cout << sum << endl;
    cout << duration.count();

    return 0;
}

bool isAllZero(vector<int>* vec) {
    for (int i = 0; i < vec->size(); i++) {
        if (vec->at(i) != 0) {
            return false;
        }
    }

    return true;
}