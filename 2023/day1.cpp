#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string numberName[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    ifstream mainData("source/day1.txt");
    int sum, wordLen = 0;
    int trueNum, firstNum, lastNum = -1;
    string lastRead = "";
    string dataCopy;
    vector<string> data;

    while (getline(mainData, lastRead))
        data.push_back(lastRead);

    for (int i = 0; i < data.size(); i++)
    {
        firstNum = -1;
        lastNum = -1;

        wordLen = data[i].length();
        dataCopy = data[i];
        for (int j=0;j<wordLen;j++)
        {
            // cout << "Word: " << dataCopy;
            
            try {
                firstNum = stoi(dataCopy.substr(0, 1));
            }
            catch (const std::invalid_argument& ia) {
                // std::cerr << "Invalid argument: " << ia.what() << '\n';
                for (int k=0;k<9;k++)
                {
                    if(dataCopy.length() >= numberName[k].length())
                        if(dataCopy.substr(0, numberName[k].length()) == numberName[k])
                        {
                            firstNum = k+1;
                            break;
                        }    
                }
            }

            dataCopy = dataCopy.substr(1);
            // std::cout << " | Num: " << firstNum << " | NewWord: " << dataCopy << endl;

            if(firstNum != -1)
                break;
        }
        dataCopy = data[i];
        for (int j=0;j<wordLen;j++)
        {
            // cout << "Word: " << dataCopy;

            try {
                lastNum = stoi(dataCopy.substr(dataCopy.length()-1, 1));
            }
            catch (const std::invalid_argument& ia) {
                // std::cerr << "Invalid argument: " << ia.what() << '\n';
                for (int k=0;k<9;k++)
                {
                    // cout << " | CheckNum-" << k+1 << ": " << dataCopy.substr(dataCopy.length()-numberName[k].length(), numberName[k].length());
                    if(dataCopy.length() >= numberName[k].length())
                        if(dataCopy.substr(dataCopy.length()-numberName[k].length(), numberName[k].length()) == numberName[k])
                        {
                            lastNum = k+1;
                            // cout << " | FoundNum: " << lastNum << endl;
                            break;
                        }
                }
            }

            dataCopy = dataCopy.substr(0, dataCopy.length()-1);
            // std::cout << " | Num: " << lastNum << " | NewWord: " << dataCopy << endl;

            if(lastNum != -1)
                break;
        }
        if(firstNum != -1 && lastNum != -1)
            trueNum = (firstNum*10) + lastNum;
        else
            trueNum = 0;
        sum += trueNum;
        cout << "Word: " << data[i] << "\n\t| F#: " << firstNum << " | L#: " << lastNum << " | T#: " << trueNum << " | Sum: " << sum << endl;
        // cout << "\nNewLine\n";
    }
    return 0;
}