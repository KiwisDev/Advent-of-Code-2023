#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool isWinning(vector<int>* v, int n);

int main() {
    ifstream file("inputs/puzzle.txt");
    string line;
    
    int sum = 0;

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

        int points = 0;
        for (int i = 0; i < card.size(); i++) {
            if (isWinning(&win, card[i])) {
                if (points == 0) {
                    points = 1;
                }
                else {
                    points *= 2;
                }
            }
        }

        sum += points;
    }

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
