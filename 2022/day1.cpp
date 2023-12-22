#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    ifstream mainData("sourceFile/day1.txt");

    vector<int> attendecne;

    int numElves = 0;
    int elfValue;
    int lastValue;
    string lastRead = "";
    stringstream conv;
    int maxCal = 0;
    int maxCalLocation;
    int topThree[3];

    while (getline(mainData, lastRead))
    {
        if (lastRead.empty())
        {
            attendecne.push_back(elfValue);
            cout << elfValue << "   " << numElves++ << endl;
            elfValue = 0;
        }
        else
        {
            istringstream tmp(lastRead);
            tmp >> lastValue;
            elfValue += lastValue;
        }
    }
    attendecne.push_back(elfValue);
    cout << endl;

    for(int j=0;j<3;j++)
    {
        for (int i=0;i<attendecne.size();i++)
        {
            if(attendecne[i] > maxCal)
            {
                maxCal = attendecne[i];
                maxCalLocation = i;
            }
            // maxCal = max(attendecne[i], maxCal);
        }
        cout << endl << maxCal;
        topThree[j] = maxCal;
        
        maxCal = 0;
        attendecne[maxCalLocation] = 0;
        // attendecne.erase(attendecne.begin() + maxCalLocation-1);

    }

    cout << endl << topThree[0] + topThree[1] + topThree[2];
    return 0;
}