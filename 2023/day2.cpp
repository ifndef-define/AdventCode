#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


int main()
{
    ifstream rawData("source/day2.txt");
    vector<string> data;
    string full_line, matchLine, colorLine, color;

    while(getline(rawData, full_line))
        data.push_back(full_line);

    const int red = 12;
    const int green = 13;
    const int blue = 14;
    int game, redCount, redHigh, greenCount, greenHigh, blueCount, blueHigh, commaCount = 0;

    int sum = 0;
    int power = 0;

    for (int i=0; i<data.size(); i++)
    {
        redCount = 0;
        greenCount = 0;
        blueCount = 0;
        redHigh = 0;
        greenHigh = 0;
        blueHigh = 0;


        full_line = data[i].substr(5, data[i].find_first_of(":")-5);
        game = stoi(full_line);
        cout << "==========================\n" << "Game: " << game << endl;
        // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
        data[i] = data[i].substr(data[i].find_first_of(":")+2);
        while (data[i].length() > 0)
        {
            redCount = 0;
            greenCount = 0;
            blueCount = 0;
            
            cout << "\nData: " << data[i] << endl;
            matchLine = data[i].substr(0, data[i].find_first_of(";"));
            
            colorLine = matchLine.substr(0, matchLine.find_first_of(","));

            commaCount = 0;

            for (int j=0; j < matchLine.length(); j++)
                if (matchLine[j] == ',')
                    commaCount++;
                    
            while (commaCount >= 0)
            {

                cout << "ML: " << matchLine << " | CL: " << colorLine << endl;
                color = colorLine.substr(colorLine.find_first_of(" ")+1);
                
                if (color == "red")
                    redCount = stoi(colorLine.substr(0, colorLine.find_first_of(" ")));
                else if (color == "green")
                    greenCount = stoi(colorLine.substr(0, colorLine.find_first_of(" ")));
                else if (color == "blue")
                    blueCount = stoi(colorLine.substr(0, colorLine.find_first_of(" ")));

                cout << "\t" << color << " " << redCount << " " << greenCount << " " << blueCount << " | C: " << commaCount << endl;

                matchLine = matchLine.substr(matchLine.find_first_of(",") + 2);
                if (commaCount > 1)
                    colorLine = matchLine.substr(0, matchLine.find_first_of(","));
                else
                    colorLine = matchLine;

                commaCount--;

            }

            if (redCount > redHigh)
                redHigh = redCount;
            if (greenCount > greenHigh)
                greenHigh = greenCount;
            if (blueCount > blueHigh)
                blueHigh = blueCount;

            // if(!(redCount <= red && greenCount <= green && blueCount <= blue))
            // {
            //     cout << "Game: " << game << " is Invalid!" << endl;
            //     goto end;
            // }

            if (data[i].find_first_of(";") == string::npos)
                data[i] = "";
            else
                data[i] = data[i].substr(data[i].find_first_of(";")+2);
        }

        power = (redHigh * greenHigh * blueHigh);
        sum += power;
        cout << "Minimums: \nRed: " << redHigh << " | Green: " << greenHigh << " | Blue: " << blueHigh << " | Power: " << power << " | Sum: " << sum << endl;
        // continue;

        // end:
        // continue;        
    }

    cout << "\n\nSum: " << sum << endl;
    
    return 0;
}