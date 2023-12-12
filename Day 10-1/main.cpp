#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NUL
} Direction;

typedef struct {
    int NORTH;
    int EAST;
    int SOUTH;
    int WEST;
} Node;

typedef struct {
    int x;
    int y;
} Pos;

bool findCycle(Pos* pos, vector<vector<Node>>* graph, int dir, vector<Node>* cycle);

int main() {
    auto startChrono = chrono::high_resolution_clock::now();

    fstream file("inputs/sample1.txt");
    string line;

    vector<vector<Node>> graphs;
    Pos startPos;
    vector<Node> cycle;

    int lineCount = 0;
    while (getline(file, line)) { // Read file
        vector<Node> nodes;

        for (int i = 0; i < line.size(); i++) {
            switch (line[i]) {
            case '|':
                nodes.push_back({ 1, 0, 1, 0 });
                break;

            case '-':
                nodes.push_back({ 0, 1, 0, 1 });
                break;

            case 'L':
                nodes.push_back({ 1, 1, 0, 0 });
                break;

            case 'J':
                nodes.push_back({ 1, 0, 0, 1 });
                break;

            case '7':
                nodes.push_back({ 0, 0, 1, 1 });
                break;

            case 'F':
                nodes.push_back({ 0, 1, 1, 0 });
                break;
                
            case 'S':
                startPos.x = i;
                startPos.y = lineCount;
                break;

            default:
                nodes.push_back({ 0, 0, 0, 0 });
            } 
        }
        graphs.push_back(nodes);
        ++lineCount;
    }

    for (int i = 0; i < 4; i++) { // Try to find a loop in each of 4 directions
        if (findCycle(&startPos, &graphs, i, &cycle)) {
            cout << "find cycle" << endl;
            //break;
        }
    }

    auto endChrono = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(endChrono - startChrono);

    std::cout << duration.count();

    return 0;
}

bool findCycle(Pos* pos, vector<vector<Node>>* graph, int dir, vector<Node>* cycle) {
    Pos currentPos = *pos;
    vector<Node> tmpCycle;
    Direction comming = NUL;

    switch (dir) {
    case NORTH: // North
        if (currentPos.y - 1 >= 0) {
            currentPos.y -= 1;
            tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
            comming = SOUTH;
        }
        break;

    case EAST: // East
        if (currentPos.x + 1 < graph->at(currentPos.x).size()) {
            currentPos.x += 1;
            tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
            comming = WEST;
        }
        break;

    case SOUTH: // South
        if (currentPos.y + 1 < graph->size()) {
            currentPos.y += 1;
            tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
            comming = NORTH;
        }
        break;

    case WEST:
        if (currentPos.x - 1 >= 0) {
            currentPos.x -= 1;
            tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
            comming = EAST;
        }
        break;
    }

    if (comming == NUL) {
        return false;
    }

    while (currentPos.x != pos->x || currentPos.y != pos->y) {
        Node* currentNode = &graph->at(currentPos.y).at(currentPos.x);

        if(currentNode->NORTH == 1 && comming != NORTH) { // Check if 2nd connection to north
            if (currentPos.y - 1 >= 0) {
                currentPos.y -= 1;
                tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
                comming = SOUTH;
            }
            else {
                return false;
            }
        }
        else if (currentNode->EAST == 1 && comming != EAST) { // Check if 2nd connection to east
            if (currentPos.x + 1 < graph->at(currentPos.x).size()) {
                currentPos.x += 1;
                tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
                comming = WEST;
            }
            else {
                return false;
            }
        }
        else if (currentNode->SOUTH == 1 && comming != SOUTH) { // Check if 2nd connection to south
            if (currentPos.y + 1 < graph->size()) {
                currentPos.y += 1;
                tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
                comming = NORTH;
            }
            else {
                return false;
            }
        }
        else if (currentNode->WEST == 1 && comming != WEST) { // Check if 2nd connection to west
            if (currentPos.x - 1 >= 0) {
                currentPos.x -= 1;
                tmpCycle.push_back(graph->at(currentPos.y).at(currentPos.x));
                comming = EAST;
            }
            else {
                false;
            }
        }
    }

    for (int i = 0; i < tmpCycle.size(); i++) {
        cycle->push_back(tmpCycle[i]);
    }

    return true;
}