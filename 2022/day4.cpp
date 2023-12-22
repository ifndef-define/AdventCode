#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    fstream mainData("sourceFile/day4.txt");
    int numContained = 0;
    int firstRange[2] = {0,0};
    int secondRange[2] = {0,0};
    string currentElves;
    getline(mainData, currentElves);

    int comma = 0;
    int dash1 = 0;
    int dash2 = 0;

    while(mainData)
    {
        comma = currentElves.find_first_of(',');
        dash1 = currentElves.find_first_of('-');
        dash2 = currentElves.find_first_of('-', comma);

        firstRange[0] = stoi(currentElves.substr(0, dash1));
        firstRange[1] = stoi(currentElves.substr(dash1+1, comma-dash1-1));
        secondRange[0] = stoi(currentElves.substr(comma+1, dash2-comma-1));
        secondRange[1] = stoi(currentElves.substr(dash2+1));

        // cout << firstRange[0] << endl << firstRange[1] << endl << secondRange[0] << endl << secondRange[1] << endl;

        if(firstRange[0] < secondRange[0])
        {
            if(firstRange[1] >= secondRange[0])
            {
                numContained++;
            }
        }
        else if(firstRange[0] > secondRange[0])
        {
            if(firstRange[0] <= secondRange[1])
            {
                numContained++;
            }
        }
        else
        {
            numContained++;
        }

        // if((firstRange[1] >= secondRange[0] && firstRange[0] <= secondRange[1]) || (firstRange[0] <= secondRange[1] && firstRange[0] <= secondRange[1]))
        // {
        //     numContained++;
        // }

        getline(mainData, currentElves);
    }

    cout << numContained;
    return 0;
}

/*
.234.....  2-4
.....678.  6-8

...456...  2-3
.234.....  4-5

....567..  5-7
......789  7-9

.2345678.  2-8
..34567..  3-7
*/