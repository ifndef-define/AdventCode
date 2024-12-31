#include "../useful.hpp"

/**
 * Day 3 Puzzle
 * Part 2
 * 
 * https://adventofcode.com/2015/day/3
 * 
 */

bool hasVisited(vector<pair<int,int>> &v, int x, int y) {
    for (int i=0; i<v.size(); i++)
        if (v[i].first == x && v[i].second == y)
            return true;

    return false;
}

int main() {

    ifstream inp_file("inputs/day3.txt");
    string directions;
    getline(inp_file, directions);

    vector<pair<int, int>> visited;
    visited.push_back({0,0});
    int houses = 1;
    bool santaTurn = true;
    pair<int, int> santaPos = {0,0};
    pair<int, int> roboPos = {0,0};

    for (int i=0; i<directions.length(); i++) {
        if (directions[i] == '^') {
            if (santaTurn)
                santaPos.second++;
            else
                roboPos.second++;
        } else if (directions[i] == 'v') {
            if (santaTurn)
                santaPos.second--;
            else
                roboPos.second--;
        } else if (directions[i] == '<') {
            if (santaTurn)
                santaPos.first--;
            else
                roboPos.first--;
        } else if (directions[i] == '>') {
            if (santaTurn)
                santaPos.first++;
            else
                roboPos.first++;
        }

        if (santaTurn) {
            if (!hasVisited(visited, santaPos.first, santaPos.second)) {
                visited.push_back({santaPos.first, santaPos.second}); 
                houses++;
            }
        } else {
            if (!hasVisited(visited, roboPos.first, roboPos.second)) {
                visited.push_back({roboPos.first, roboPos.second}); 
                houses++;
            }
        }
        santaTurn = !santaTurn;
    }

    cout << "Houses: " << houses << endl;

    return 0;
}
