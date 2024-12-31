#include "../useful.hpp"

/**
 * Day 1 Puzzle
 * Part 1
 * 
 * https://adventofcode.com/2015/day/1
 * 
 */

int main() {

    ifstream input("inputs/day1.txt");
    string input_str;
    getline(input, input_str);

    int floor = 0;
    for (int i=0; i<input_str.length(); i++) {
        if (input_str[i] == '(') {
            floor++;
        } else {
            floor--;
        }
    }

    cout << "Floor: " << floor << endl;

    return 0;
}