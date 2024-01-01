#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string symbol = "`~!@#$%^&*()_-+={[}}|\\:;\"'<,>.?/]}";

// Line 126 112 #84
=======================================
Line 124 :
...................52..170...*......459................/...#.......161........813.510.........207......@..........581..................*....
Ratio : 52
         | * | . | . | . | .
         | . | 5 | 2 | . | .
         | . | . | . | . | .
Valid Ratio | Sum : 527251
Ratio : 170
         | . | . | . | . | .
         | . | 1 | 7 | 0 | .
         | . | . | * | . | .
Valid Ratio | Sum : 527421
Ratio : 459
         | . | . | . | . | *
         | . | 4 | 5 | 9 | .
         | . | . | . | . | .
Valid Ratio | Sum : 527880
Ratio : 161
         | . | . | . | . | .
         | . | 1 | 6 | 1 | .
         | . | . | . | . | .
Valid Ratio | Sum : 528041
Ratio : 813
         | . | . | . | . | .
         | . | 8 | 1 | 3 | .
         | . | * | . | . | .
Valid Ratio | Sum : 528854
Ratio : 510
         | . | . | * | . | .
         | . | 5 | 1 | 0 | .
         | . | . | . | . | .
Valid Ratio | Sum : 529364
Ratio : 207
         | * | . | . | . | .
         | . | 2 | 0 | 7 | .
         | . | . | . | . | .
Valid Ratio | Sum : 529571
Ratio : 581
         | . | . | . | . | .
         | . | 5 | 8 | 1 | .
         | . | . | . | . | .
Valid Ratio | Sum : 530152
=======================================
Line 125 :
............#...........*..978...........581.9*815..........450...............*.......................................604.......308...725...
Ratio : 978
         | . | . | . | * | .
         | . | 9 | 7 | 8 | .
         | . | . | . | . | .
Valid Ratio | Sum : 531130
Ratio : 581
         | . | . | . | . | .
         | . | 5 | 8 | 1 | .
         | / | . | . | . | .
Valid Ratio | Sum : 531711
Ratio : 9
         | . | . | .
         | . | 9 | *
         | . | . | .
Valid Ratio | Sum : 531720
Ratio : 815
         | . | . | . | . | .
         | * | 8 | 1 | 5 | .
         | . | . | . | . | .
Valid Ratio | Sum : 532535
Ratio : 450
         | # | . | . | . | .
         | . | 4 | 5 | 0 | .
         | . | . | . | . | .
Valid Ratio | Sum : 532985
Ratio : 604
         | . | . | . | . | .
         | . | 6 | 0 | 4 | .
         | . | . | - | . | .
Valid Ratio | Sum : 533589
Ratio : 308
         | . | . | . | . | .
         | . | 3 | 0 | 8 | .
         | . | . | . | . | .
Valid Ratio | Sum : 533897
Ratio : 725
         | . | . | * | . | .
         | . | 7 | 2 | 5 | .
         | . | . | . | . | .
Valid Ratio | Sum : 534622
=======================================
Line 126 :
............16.........269............../.............195........217*216......890......................534.....84......-......-.............
Ratio : 16
         | . | # | . | . | .
         | . | 1 | 6 | . | .
         | . | . | . | . | .
Valid Ratio | Sum : 534638
Ratio : 269
         | . | . | * | . | .
         | . | 2 | 6 | 9 | .
         | . | . | . | . | .
Valid Ratio | Sum : 534907
Ratio : 195
         | . | . | . | . | .
         | . | 1 | 9 | 5 | .
         | . | . | . | . | *
Valid Ratio | Sum : 535102
Ratio : 217
         | . | . | . | . | .
         | . | 2 | 1 | 7 | *
         | . | . | . | . | .
Valid Ratio | Sum : 535319
Ratio : 216
         | . | . | . | . | .
         | * | 2 | 1 | 6 | .
         | . | . | . | . | .
Valid Ratio | Sum : 535535
Ratio : 890
         | . | * | . | . | .
         | . | 8 | 9 | 0 | .
         | . | . | . | . | .
Valid Ratio | Sum : 536425
Ratio : 534
         | . | . | . | . | .
         | . | 5 | 3 | 4 | .
         | . | . | * | . | .
Valid Ratio | Sum : 536959
Ratio : 84
         | . | . | . | . | .
         | . | 8 | 4 | . | .
         | . | . | . | . | .
Valid Ratio | Sum : 537043
=======================================

int main()
{
    ifstream rawData("source/day3.txt");
    vector<string> data;
    string line, lineTemp, ratio_str, symbolInArr;

    int sum, ratio = 0;
    bool validRatio = false;

    while(getline(rawData, line))
        data.push_back(line);

    for (int i = 0; i < data.size(); i++)
    {
        lineTemp = data[i];
        cout << "=======================================\n" << "Line " << i+1 << " : \n" << lineTemp << endl;
        for (int j = 0; j < data[i].length(); j++)
        {
            symbolInArr = data[i][j];
            if (data[i][j] == '.' || symbol.find(symbolInArr) != string::npos)
                continue;

            for (int k=1;k<4;k++)
            {
                try { 
                    if (data[i][j+k] != '.' && symbol.find(data[i][j+k]) == string::npos)
                        continue;
                } catch (const std::out_of_range& oor) {
                    symbolInArr = "~"; 
                }

                ratio_str = lineTemp.substr(j, k+1);
            }
            ratio = stoi(ratio_str);
            cout << "Ratio : " << ratio << "\n\t";

            if (i!=0)
            {
                try { symbolInArr = data[i-1][j-1]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
                cout << " | " << symbolInArr;
                if (symbol.find(symbolInArr) != string::npos)
                    validRatio = true;

                for (int k=0;k<ratio_str.length();k++)
                {
                    try { symbolInArr = data[i-1][j+k]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
                    cout << " | " << symbolInArr;
                    if (symbol.find(symbolInArr) != string::npos)
                        validRatio = true;
                }
                cout << "\n\t";
            }
            
            try { symbolInArr = data[i][j-1]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
            cout << " | " << symbolInArr;
            if (symbol.find(symbolInArr) != string::npos)
                validRatio = true;

            for (int k=0;k<ratio_str.length();k++)
            {
                try { symbolInArr = data[i][j+k]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
                cout << " | " << symbolInArr;
                if (symbol.find(symbolInArr) != string::npos)
                    validRatio = true;
            }

            if (i != data.size()-1)
            {
                cout << "\n\t";
                try { symbolInArr = data[i+1][j-1]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
                cout << " | " << symbolInArr;
                if (symbol.find(symbolInArr) != string::npos)
                    validRatio = true;

                for (int k=0;k<ratio_str.length();k++)
                {
                    try { symbolInArr = data[i+1][j+k]; } catch (const std::out_of_range& oor) { symbolInArr = "~"; }
                    cout << " | " << symbolInArr;
                    if (symbol.find(symbolInArr) != string::npos)
                        validRatio = true;
                }
            }

            if (validRatio)
            {
                sum += ratio;
                cout << "\nValid Ratio" << " | Sum : " << sum << endl;
            }
            else
                cout << "\nInvalid Ratio" << " | Sum : " << sum << endl;

            validRatio = false;
            j += ratio_str.length()-1;
        }
    }

    return 0;
}