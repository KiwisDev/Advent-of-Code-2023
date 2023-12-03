#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream file("inputs/puzzle.txt");
    string line;

    vector<vector<char>> schem;
    vector<vector<bool>> finded;

    int nbLine = 0;
    int nbColumn = 0;

    int sum = 0;

    // Read data and put them in arrays
    while (getline(file, line)) {
        vector<char> buff;
        vector<bool> tmpFinded;
        for (int i = 0; i < line.length(); i++) {
            buff.push_back(line[i]);
            tmpFinded.push_back(false);
        }
        ++nbLine;
        nbColumn = line.length();
        schem.push_back(buff);
        finded.push_back(tmpFinded);
    }

    cout << "Columns : " << nbColumn << endl << "Lines : " << nbLine << endl << endl;

    // Print readed schema
    for (int y = 0; y < nbColumn; y++) {
        for (int x = 0; x < nbLine; x++) {
            cout << schem[y][x];
        }
        cout << endl;
    }

    cout << endl;

    // Find valid numbers
    for (int y = 0; y < nbColumn; y++) {
        for (int x = 0; x < nbLine; x++) {
            char c = schem[y][x];

            if (!isalnum(c) && !(c == '.')) { // Check if c is a valid symbol
                if (y - 1 >= 0 && isdigit(schem[y - 1][x]) && !finded[y - 1][x]) { // Check digit on top
                    int startX = x;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y - 1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y - 1][startX])) {
                        num.push_back(schem[y - 1][startX]);
                        finded[y - 1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (y + 1 < nbLine && isdigit(schem[y + 1][x]) && !finded[y + 1][x]) { // Check digit on bottom
                    int startX = x;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y + 1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y + 1][startX])) {
                        num.push_back(schem[y + 1][startX]);
                        finded[y + 1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (x - 1 >= 0 && isdigit(schem[y][x - 1]) && !finded[y][x - 1]) { // Check digit on left
                    int startX = x - 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y][startX])) {
                        num.push_back(schem[y][startX]);
                        finded[y][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (x + 1 < nbColumn && isdigit(schem[y][x + 1]) && !finded[y][x + 1]) { // Check digit on right
                    int startX = x + 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y][startX])) {
                        num.push_back(schem[y][startX]);
                        finded[y][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (y - 1 >= 0 && x - 1 >= 0 && isdigit(schem[y - 1][x - 1]) && !finded[y - 1][x - 1]) { // Check digit on top-left
                    int startX = x - 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y-1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y-1][startX])) {
                        num.push_back(schem[y-1][startX]);
                        finded[y-1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (y - 1 >= 0 && x < nbColumn && isdigit(schem[y - 1][x + 1]) && !finded[y - 1][x + 1]) { // Check digit on top-right
                    int startX = x + 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y - 1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y - 1][startX])) {
                        num.push_back(schem[y - 1][startX]);
                        finded[y - 1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (y + 1 < nbLine && x - 1 >= 0 && isdigit(schem[y + 1][x - 1]) && !finded[y + 1][x - 1]) { // Check digit on bottom-left
                    int startX = x - 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y + 1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y + 1][startX])) {
                        num.push_back(schem[y + 1][startX]);
                        finded[y + 1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }

                if (y + 1 < nbLine && x + 1 < nbColumn && isdigit(schem[y + 1][x + 1]) && !finded[y + 1][x + 1]) { // Check digit on bottom-right
                    int startX = x + 1;
                    string num = "";

                    while (startX - 1 >= 0 && isdigit(schem[y + 1][startX - 1])) {
                        --startX;
                    }

                    while (startX < nbColumn && isdigit(schem[y + 1][startX])) {
                        num.push_back(schem[y + 1][startX]);
                        finded[y + 1][startX] = true;
                        ++startX;
                    }

                    sum += stoi(num);
                }
            }
        }
    }

    cout << sum << endl;

    return 0;
}