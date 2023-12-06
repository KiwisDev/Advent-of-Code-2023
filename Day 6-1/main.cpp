#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef struct {
    int time;
    int record;
} Race;

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string lines[2];

    vector<int> ways;
    int result;

    getline(file, lines[0]);
    getline(file, lines[1]);

    file.close();

    vector<Race> races;

    istringstream ss[2];
    ss[0] = istringstream(lines[0]);
    ss[1] = istringstream(lines[1]);
    string buff[2];

    while (ss[0] >> buff[0] && ss[1] >> buff[1]) {
        if (isdigit(buff[0][0]) && isdigit(buff[0][0]))
            races.push_back({ stoi(buff[0]), stoi(buff[1]) });
    }

    for (int i = 0; i < races.size(); i++) {
        int count = 0;

        for (int j = 0; j < races[i].time; j++) {
            if (j * (races[i].time - j) > races[i].record)
                count++;
        }

        ways.push_back(count);
    }

    result = ways[0];
    for (int i = 1; i < ways.size(); i++) {
        result *= ways[i];
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << result << endl;

    cout << duration.count() << " s";

    return 0;
}