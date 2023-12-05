#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

void processLine(vector<string>* lines, map<unsigned long, unsigned long>* map);

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
    ifstream file("inputs/puzzle.txt");
    string line;

    Mode currentMode = SEED_TO_SOIL;

    vector<unsigned long> seeds;
    
    vector<string> lines[HUMIDITY_TO_LOCATION + 1];
    map<unsigned long, unsigned long> maps[HUMIDITY_TO_LOCATION + 1];

    thread threads[HUMIDITY_TO_LOCATION + 1];

    vector<unsigned long> results;

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

    for (int i = 0; i < HUMIDITY_TO_LOCATION + 1; i++) {
        threads[i] = thread(processLine, &lines[i], &maps[i]);
    }

    for (int i = 0; i < HUMIDITY_TO_LOCATION + 1; i++) {
        threads[i].join();
    }

    cout << "Tout est process sa mere" << endl;

    for (int i = 0; i < seeds.size(); i++) {
        unsigned long temp = seeds[i];

        if (maps[SEED_TO_SOIL].count(temp) > 0) {
            temp = maps[SEED_TO_SOIL][temp];
        }

        if (maps[SOIL_TO_FETILIZER].count(temp) > 0) {
            temp = maps[SOIL_TO_FETILIZER][temp];
        }

        if (maps[FERTILIZER_TO_WATER].count(temp) > 0) {
            temp = maps[FERTILIZER_TO_WATER][temp];
        }

        if (maps[WATER_TO_LIGHT].count(temp) > 0) {
            temp = maps[WATER_TO_LIGHT][temp];
        }

        if (maps[LIGHT_TO_TEMPERATURE].count(temp) > 0) {
            temp = maps[LIGHT_TO_TEMPERATURE][temp];
        }

        if (maps[TEMPERATURE_TO_HUMIDITY].count(temp) > 0) {
            temp = maps[TEMPERATURE_TO_HUMIDITY][temp];
        }

        if (maps[HUMIDITY_TO_LOCATION].count(temp) > 0) {
            temp = maps[HUMIDITY_TO_LOCATION][temp];
        }

        results.push_back(temp);
    }

    int min = 0;
    for (int i = 1; i < results.size(); i++) {
        if (results[i] < results[min])
            min = i;
    }

    cout << results[min] << endl;

    return 0;
}

void processLine(vector<string>* lines, map<unsigned long, unsigned long>* map) {
    cout << "Process started" << endl;
    for (int i = 0; i < lines->size(); i++) {
        istringstream ss(lines->at(i));
        string buff;

        ss >> buff;
        unsigned long dest_start = stoul(buff);

        ss >> buff;
        unsigned long src_start = stoul(buff);

        ss >> buff;
        unsigned long lenght = stoul(buff);

        for (unsigned long j = 0; j < lenght; j++) {
            map->insert(pair<unsigned long, unsigned long>(src_start + j, dest_start + j));
        }
    }
}