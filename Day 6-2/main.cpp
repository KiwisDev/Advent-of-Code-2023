#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef struct {
    unsigned long long time;
    unsigned long long record;
} Race;

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string lines[2];

    vector<unsigned long long> ways;
    unsigned long long result;

    getline(file, lines[0]);
    getline(file, lines[1]);

    file.close();

    vector<Race> races;

    istringstream ss[2];
    ss[0] = istringstream(lines[0]);
    ss[1] = istringstream(lines[1]);
    string buff[2];
    string num[2];

    while (ss[0] >> buff[0] && ss[1] >> buff[1]) {
        if (isdigit(buff[0][0]) && isdigit(buff[0][0])) {
            num[0] += buff[0];
            num[1] += buff[1];
        }
        else {
            num[0] = "";
            num[1] = "";
        }
    }

    cout << num[0] << " " << num[1] << endl;

    races.push_back({ stoull(num[0]), stoull(num[1]) });

    for (unsigned long long i = 0; i < races.size(); i++) {
        unsigned long long count = 0;

        for (unsigned long long j = 0; j < races[i].time; j++) {
            if (j * (races[i].time - j) > races[i].record)
                count++;
        }

        ways.push_back(count);
    }

    result = ways[0];
    for (unsigned long long i = 1; i < ways.size(); i++) {
        result *= ways[i];
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << result << endl;

    cout << duration.count() << " s";

    return 0;
}