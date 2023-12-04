#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool isWinning(vector<int>* v, int n);

int main() {
    string filePath = "inputs/puzzle.txt";

    ifstream file(filePath);
    string line;

    int sum = 0;

    vector<int> cardIteration;
    while (getline(file, line)) {
        cardIteration.push_back(1);
    }

    file.close();
    file.open(filePath);

    int current = 0;
    while (getline(file, line)) {
        istringstream ss(line);
        string buff;

        ss >> buff; // Ignore Card
        ss >> buff; // Ignore number

        vector<int> win;
        while (ss >> buff && buff != "|")
            win.push_back(stoi(buff));

        vector<int> card;
        while (ss >> buff)
            card.push_back(stoi(buff));

        int matching = 0;
        for (int i = 0; i < card.size(); i++) {
            if (isWinning(&win, card[i]))
                ++matching;
        }

        for (int i = 0; i < cardIteration[current]; i++) {
            for (int m = 1; m <= matching; m++) {
                if (current + m < cardIteration.size())
                    ++cardIteration[current + m];
            }
        }

        ++current;
    }

    for (int i = 0; i < cardIteration.size(); i++)
        sum += cardIteration[i];

    cout << sum;

    return 0;
}

bool isWinning(vector<int>* v, int n) {
    for (int i = 0; i < v->size(); i++) {
        if (n == v->at(i)) {
            return true;
        }
    }

    return false;
}
