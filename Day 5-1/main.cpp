#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>

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
    ifstream file("inputs/sample.txt");
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
                    seeds.push_back(stoul(buff));
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

    for (int i = 0; i < 2; i++) {
        cout << "Step " << i << endl;
        maps.clear();
        processLine(&lines[i], &maps);

        for (int x = 0; x < maps.size(); x++) {
            cout << maps[x].dest_start << " " << maps[x].src_start << " " << maps[x].length << endl;
        }

        for (int s = 0; s < seeds.size(); s++) {
            for (int m = 0; m < maps.size(); m++) {
                unsigned long mapMax = maps[m].src_start + maps[m].length;
                if (seeds[s] >= maps[m].src_start && seeds[m] < mapMax) {
                    cout << seeds[s] << " used map " << maps[m].src_start << " " << mapMax << endl;
                    unsigned long diff = seeds[s] - maps[m].src_start;
                    seeds[s] = maps[m].dest_start + diff;
                }
            }
        }

        for (int i = 0; i < seeds.size(); i++) {
            cout << seeds[i] << endl;
        }

        cout << endl;
    }

    int min = 0;
    for (int i = 1; i < seeds.size(); i++) {
        if (seeds[i] < seeds[min])
            min = i;
    }

    cout << endl << seeds[min] << endl;

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