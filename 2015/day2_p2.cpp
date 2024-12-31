#include "../useful.hpp"

/**
 * Day 2 Puzzle
 * Part 2
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
    int vol, total=0;
    char x;
    
    while(getline(input_file, present)) {
        ss.str(present);
        ss >> l >> x >> w >> x >> h;
        ss.clear();

        lw = 2*(l+w);
        wh = 2*(w+h);
        hl = 2*(h+l);

        smallest = min(lw, min(wh, hl)); 
        vol = l*w*h;

        total += smallest + vol;
    }

    cout << "Total Ribbon: " << total << endl;

    return 0;
}
