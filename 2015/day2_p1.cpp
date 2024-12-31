#include "../useful.hpp"

/**
 * Day 2 Puzzle
 * Part 1
 * 
 * https://adventofcode.com/2015/day/2
 * 
 */

int main() {

    ifstream input_file("inputs/day2.txt");

    string present;
    stringstream ss;
    int l, w, h;
    int lw, wh, hl;
    int smallest;
    int sa, total=0;
    char x;
    
    while(getline(input_file, present)) {
        ss.str(present);
        ss >> l >> x >> w >> x >> h;
        ss.clear();

        lw = l*w;
        wh = w*h;
        hl = h*l;

        smallest = min(lw, min(wh, hl)); 
        sa = 2*(lw + wh + hl) + smallest;

        total += sa;
    }

    cout << "Total SA: " << total << endl;

    return 0;
}
