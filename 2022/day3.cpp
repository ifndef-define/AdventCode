#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream mainData("sourceFile/day3.txt");
    string backpack1;
    string backpack2;
    string backpack3;
    int duplicate = 0;
    int sum = 0;
    int priortity =0;
    int lines = 0;
    getline(mainData, backpack1);
    getline(mainData, backpack2);
    getline(mainData, backpack3);

    while(mainData)
    {
        duplicate = 0;
        priortity = 0;
        int i,j, k;
        for(i=0;i<backpack1.length();i++)
        {
            for(j=0;j<backpack2.length();j++)
            {
                for(k=0;k<backpack3.length();k++)
                {
                    if(backpack1[i] == backpack2[j] && backpack1[i] == backpack3[k] && backpack3[k] == backpack2[j])
                        {duplicate = backpack1[i]; break;}
                }
            }

            if(duplicate != 0)
                break;
        }

        priortity = (duplicate >= 65 && duplicate <= 90) ? duplicate - 38 : duplicate - 96;

        sum += priortity;
        lines += 3;
        cout << "Duplicate is " << (char)duplicate << " ascii value of " << duplicate << " with priority " << priortity << " at line " << lines << endl;
        getline(mainData, backpack1);
        getline(mainData, backpack2);
        getline(mainData, backpack3);
    }
    // cout << lines << endl;
    cout << sum;

    return 0;
}