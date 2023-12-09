#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

int zCount = 0;

typedef struct {
    string left;
    string right;
} Node;

bool finished(vector<string>* nodes);

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string line;

    string sequence;
    map<string, Node> tree;

    int count = 0;
    vector<string> currentNodes;

    getline(file, sequence);    // Read direction sequence
    getline(file, line);    // Skip empty line

    while (getline(file, line)) {
        istringstream ss(line);
        string buff;

        ss >> buff; // Read name
        string name = buff;

        ss >> buff; // Skip '='

        ss >> buff; // Read left
        string left = buff.substr(1, 3);

        ss >> buff; // Read right
        string right = buff.substr(0, 3);

        tree.insert(pair<string, Node>(name, { left,right }));

        if (name[2] == 'A') {
            currentNodes.push_back(name);
        }
    }

    while (!finished(&currentNodes)) {
        for (int i = 0; i < currentNodes.size(); i++) {
            if (sequence[count % sequence.size()] == 'R') {
                currentNodes[i] = tree[currentNodes[i]].right;
            }
            else {
                currentNodes[i] = tree[currentNodes[i]].left;
            }
        }

        ++count;
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << "At least 1 Z : " << zCount;
    cout << count << endl;
    cout << duration.count();

    return 0;
}

bool finished(vector<string>* nodes) {
    int count = 0;
    for (int i = 0; i < nodes->size(); i++) {
        if (nodes->at(i)[2] == 'Z') {
            ++count;
        }
    }

    if (count > 0) {
        zCount++;
    }

    return (count == nodes->size());
}
