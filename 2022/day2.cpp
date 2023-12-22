#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define ROCK        1
#define PAPER       2
#define SCISSOR     3

#define LOST        0
#define DRAW        3
#define WIN         6

int scoreCount(string round)
{
    // ifstream mainData1(file);
    // string round;
    int myPoints = 0;
    int lastAdd = 0;

    int elf;
    int me;

    // while(mainData1)
    // {
        // getline(mainData1, round);

        if(round.front() == 'A')
            elf = ROCK;
        else if(round.front() == 'B')
            elf = PAPER;
        else
            elf = SCISSOR;

        if(round.back() == 'X')
            me = ROCK;
        else if(round.back() == 'Y')
            me = PAPER;
        else
            me = SCISSOR;

        if(elf == me)
            myPoints = (me + DRAW);
        else if(elf == ROCK)
        {
            if(me == PAPER)
                myPoints = (WIN + me);
            else if(me == SCISSOR)
                myPoints = (LOST + me);
        }
        else if(elf == PAPER)
        {
            if(me == ROCK)
                myPoints = (LOST + me);
            else if(me == SCISSOR)
                myPoints = (WIN + me);
        }
        else if(elf == SCISSOR)
        {
            if(me == ROCK)
                myPoints = (WIN + me);
            else if(me == PAPER)
                myPoints = (LOST + me);
        }
        // lastRound = lastAdd;
        // myPoints += lastAdd;
        // lastAdd = 0;
    // }
    // myPoints -= lastRound;

    return myPoints;
    // cout << "You have; " << myPoints << " points!\n";
}

int main()
{
    ifstream mainData2("sourceFile/day2.txt");

    string round;
    string roundStat;
    int elf;
    int me;
    int score;
    int lastRound = 0;

    while(mainData2)
    {
        getline(mainData2, round);

        if(round.front() == 'A')
            elf = ROCK;
        else if(round.front() == 'B')
            elf = PAPER;
        else
            elf = SCISSOR;

        if(round.back() == 'X')
            me = LOST;
        else if(round.back() == 'Y')
            me = DRAW;
        else
            me = WIN;

        if(elf == ROCK)
        {
            if(me == LOST)
                roundStat = "A Z";
            else if(me == DRAW)
                roundStat = "A X";
            else
                roundStat = "A Y";
        }
        else if(elf == PAPER)
        {
            if(me == LOST)
                roundStat = "B X";
            else if(me == DRAW)
                roundStat = "B Y";
            else
                roundStat = "B Z";
        }
        else
        {
            if(me == LOST)
                roundStat = "C Y";
            else if(me == DRAW)
                roundStat = "C Z";
            else
                roundStat = "C X";
        }
        lastRound = scoreCount(roundStat);
        score += lastRound;
        // myfile << roundStat;
    }
    score -= lastRound;
    // myfile.close();
    cout << score;

    return 0;
}