#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

#include "maps.h"

using namespace std;

void processLine(vector<string>* lines, vector<Maps>* map);

enum Mode {
    SEED_TO_SOIL,
    SOIL_TO_FETILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMPERATURE,
    TEMPERATURE_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION
};

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    ifstream file("inputs/puzzle.txt");
    string line;

    Mode currentMode = SEED_TO_SOIL;

    vector<unsigned long> seeds;

    vector<string> lines[HUMIDITY_TO_LOCATION + 1];
    vector<Maps> maps;

    while (getline(file, line)) {
        istringstream ss(line);
        string buff;

        if (!isdigit(line[0])) { // Check if section title
            ss >> buff;

            if (buff == "seeds:") { // Initial seeds list
                while (ss >> buff) {
                    unsigned long start = stoul(buff);

                    ss >> buff;
                    unsigned long length = stoul(buff);

                    for(unsigned long i=0; i<length; i++)
                        seeds.push_back(start + i);
                }
            }
            else if (buff == "seed-to-soil") {
                currentMode = SEED_TO_SOIL;
            }
            else if (buff == "soil-to-fertilizer") {
                currentMode = SOIL_TO_FETILIZER;
            }
            else if (buff == "fertilizer-to-water") {
                currentMode = FERTILIZER_TO_WATER;
            }
            else if (buff == "water-to-light") {
                currentMode = WATER_TO_LIGHT;
            }
            else if (buff == "light-to-temperature") {
                currentMode = LIGHT_TO_TEMPERATURE;
            }
            else if (buff == "temperature-to-humidity") {
                currentMode = TEMPERATURE_TO_HUMIDITY;
            }
            else if (buff == "humidity-to-location") {
                currentMode = HUMIDITY_TO_LOCATION;
            }
        }
        else { // Put number int the correct location
            lines[currentMode].push_back(line);
        }
    }

    file.close();

    for (int i = 0; i < HUMIDITY_TO_LOCATION + 1; i++) {
        cout << "Step " << i + 1 << endl;
        maps.clear();
        processLine(&lines[i], &maps);

        for (int s = 0; s < seeds.size(); s++) {
            for (int m = 0; m < maps.size(); m++) {
                if (seeds[s] >= maps[m].src_start && seeds[s] < maps[m].src_start + maps[m].length) {
                    unsigned long diff = seeds[s] - maps[m].src_start;
                    seeds[s] = maps[m].dest_start + diff;
                    break;
                }
            }
        }
    }

    int min = 0;
    for (int i = 1; i < seeds.size(); i++) {
        if (seeds[i] < seeds[min])
            min = i;
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endChrono - startChrono);

    cout << seeds[min] << endl;

    cout << duration.count() << " s";

    return 0;
}

void processLine(vector<string>* lines, vector<Maps>* map) {
    for (int i = 0; i < lines->size(); i++) {
        istringstream ss(lines->at(i));
        string buff;

        ss >> buff;
        unsigned long dest_start = stoul(buff);

        ss >> buff;
        unsigned long src_start = stoul(buff);

        ss >> buff;
        unsigned long length = stoul(buff);

        map->push_back(Maps(src_start, dest_start, length));
    }
}