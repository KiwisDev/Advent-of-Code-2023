#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef struct {
    string left;
    string right;
} Node;

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string line;

    string sequence;
    map<string, Node> tree;

    int count = 0;
    string currentNode = "AAA";

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
    }

    while (currentNode != "ZZZ") {
        if (sequence[count % sequence.size()] == 'R') {
            currentNode = tree[currentNode].right;
        }
        else {
            currentNode = tree[currentNode].left;
        }

        ++count;
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << count << endl;
    cout << duration.count();

    return 0;
}
