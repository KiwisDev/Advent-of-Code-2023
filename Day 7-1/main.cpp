#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef enum {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
} Type;

typedef struct {
    string cards;
    int bid;
} Hand;

bool compareHands(Hand* h1, Hand* h2); // Return true if h1 worth more than h2 //

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/sample.txt");
    string line;

    vector<Hand> hands;

    while (getline(file, line)) {
        istringstream ss(line);
        string buff, cards, bid;

        ss >> cards;
        ss >> bid;

        Hand hand({ cards, stoi(bid) });

        if (hands.size() == 0) {
            hands.push_back(hand);
        }
        else {
            bool placed = false;
            for (int i = 0; i < hands.size(); i++) {
                if (placed == false && compareHands(&hands[i], &hand)) {
                    hands.insert(hands.begin() + i, hand);
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                hands.push_back(hand);
            }
        }
    }

    file.close();

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << duration.count() << " s";

    return 0;
}

bool compareHands(Hand* h1, Hand* h2) {
    // -- h1 type -- //
    Type h1Type = HIGH_CARD;
    map<char, int> count1;

    for (int i = 0; i < 5; i++) {
        char c = h1->cards[i];
        if (count1.find(c) != count1.end()) {
            count1[c]++;
        }
        else {
            count1.insert(pair<char, int>(c, 1));
        }
    }

    if (count1.size() == 1) {
        h1Type = FIVE_OF_A_KIND;
    }
    else if (count1.size() == 2) {
        vector<char> keys;
        for (map<char, int>::iterator it = count1.begin(); it != count1.end(); it++) {
            keys.push_back(it->first);
        }

        if (count1[keys[0]] == 4 || count1[keys[0]] == 1) {
            h1Type = FOUR_OF_A_KIND;
        }
        else {
            h1Type = FULL_HOUSE;
        }
    }
    else if (count1.size() == 3) {
        vector<char> keys;
        for (map<char, int>::iterator it = count1.begin(); it != count1.end(); it++) {
            keys.push_back(it->first);
        }

        if (count1[keys[0]] == 3 || count1[keys[1]] == 3 || count1[keys[2]] == 3) {
            h1Type = THREE_OF_A_KIND;
        }
        else {
            h1Type = TWO_PAIR;
        }
    }
    else if (count1.size() == 4) {
        h1Type = ONE_PAIR;
    }

    // -- h2 type -- //
    Type h2Type = HIGH_CARD;
    map<char, int> count2;

    for (int i = 0; i < 5; i++) {
        char c = h2->cards[i];
        if (count2.find(c) != count2.end()) {
            count2[c]++;
        }
        else {
            count2.insert(pair<char, int>(c, 1));
        }
    }

    if (count2.size() == 1) {
        h2Type = FIVE_OF_A_KIND;
    }
    else if (count2.size() == 2) {
        vector<char> keys;
        for (map<char, int>::iterator it = count2.begin(); it != count2.end(); it++) {
            keys.push_back(it->first);
        }

        if (count2[keys[0]] == 4 || count2[keys[0]] == 1) {
            h2Type = FOUR_OF_A_KIND;
        }
        else {
            h2Type = FULL_HOUSE;
        }
    }
    else if (count2.size() == 3) {
        vector<char> keys;
        for (map<char, int>::iterator it = count2.begin(); it != count2.end(); it++) {
            keys.push_back(it->first);
        }

        if (count2[keys[0]] == 3 || count2[keys[1]] == 3 || count2[keys[2]] == 3) {
            h2Type = THREE_OF_A_KIND;
        }
        else {
            h2Type = TWO_PAIR;
        }
    }
    else if (count2.size() == 4) {
        h2Type = ONE_PAIR;
    }

    return false;
}