#include "../useful.hpp"

/**
 * Day 3 Puzzle
 * Part 1
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
    pair<int, int> pos = {0,0};

    for (int i=0; i<directions.length(); i++) {
        if (directions[i] == '^') {
            pos.second++;
        } else if (directions[i] == 'v') {
            pos.second--;
        } else if (directions[i] == '<') {
            pos.first--;
        } else if (directions[i] == '>') {
            pos.first++;
        }

        if (!hasVisited(visited, pos.first, pos.second)) {
            visited.push_back({pos.first, pos.second}); 
            houses++;
        }
    }

    cout << "Houses: " << houses << endl;

    return 0;
}
