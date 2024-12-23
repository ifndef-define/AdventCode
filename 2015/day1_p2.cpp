#include "../useful.hpp"

/**
 * Day 1 Puzzle
 * Part 2
 * 
 * https://adventofcode.com/2015/day/1
 * 
 */

/* Steps to Solve
1) Read the file to get the input string and store into a varible
2) Iterate through the string to find '(' ')'
    a) If '(' then increase counter by 1
    b) If ')' then decrease counter by 1
    c) If counter(floor) equals '-1', break
3) Print current position
*/

int main() {

    // Step 1 //
    ifstream input("inputs/day1.txt");
    string input_str;
    getline(input, input_str);

    // Step 2 //
    int floor = 0;
    for (int i=0; i<input_str.length(); i++) {
        if (input_str[i] == '(') {
            floor++;
        } else {
            floor--;
        }

        if (floor == -1) {
            // Step 3 //
            cout << "Position: " << ++i << endl;
            break;
        }
    }

    return 0;
}