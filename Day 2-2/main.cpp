#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

using namespace std;

int main() {
    ifstream file("inputs/puzzle.txt");
    string line;

    vector<int> validGames;
    int power = 0;

    while (getline(file, line)) {
        int gameID;
        string sData;
        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        string buff;
        stringstream ss(line);

        ss >> buff; // Ignore "Game"
        ss >> buff; // Read Game ID

        gameID = stoi(buff);

        while (ss >> buff) {
            sData.append(buff + " ");
        }

        cout << gameID << endl;
        string sSets[10];

        ss = stringstream(sData);
        for (int i = 0; i < 10; i++) {
            bool end = false;

            while (!end && ss >> buff) {
                if (buff[buff.length() - 1] != ';') {
                    sSets[i].append(buff + " ");
                }
                else {
                    sSets[i].append(buff.substr(0, buff.length() - 1));
                    end = true;
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            ss = stringstream(sSets[i]);

            while (ss >> buff) {
                int num = stoi(buff);
                ss >> buff;

                if (buff[0] == 'r') {
                    if (num > maxRed) {
                        maxRed = num;
                    }
                }
                else if (buff[0] == 'g') {
                    if (num > maxGreen) {
                        maxGreen = num;
                    }
                }
                else if (buff[0] == 'b') {
                    if (num > maxBlue) {
                        maxBlue = num;
                    }
                }
            }
        }

        power += maxRed * maxGreen * maxBlue;

        if (maxRed <= MAX_RED && maxGreen <= MAX_GREEN && maxBlue <= MAX_BLUE) {
            if ((maxRed + maxGreen + maxBlue) <= (MAX_RED + MAX_GREEN + MAX_BLUE)) {
                validGames.push_back(gameID);
            }
        }

        cout << endl;
    }

    int sum = 0;
    for (int i = 0; i < validGames.size(); i++) {
        sum += validGames[i];
    }

    cout << sum << endl;
    cout << power << endl;

    return 0;
}