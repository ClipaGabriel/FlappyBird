#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
#include "score.h"
using namespace std;


int Score::import_file()
{
    scores.open("score.txt", ios::in);
    if (scores.good() == false)
    {
        cout << "Error! score.txt";
        return -1;
    }

    while(getline(scores, line))
    {
        if (atoi(line.c_str()) % 128 == 0)
        best_score = atoi(line.c_str()) / 128;
        else
        {
            return -1;
        }
    }
    scores.close();
        return 1;
}

bool Score::check(int actuall_result)
{
    if (best_score < actuall_result)
    {
        best_score = actuall_result;
        return true;
    }
    return false;
}

void Score::save()
{
    scores.open("score.txt", ios::out);
    scores<<(best_score * 128);
    scores.close();

}

string Score::return_points()
{
    stringstream points_ss;
    points_ss << best_score;
    string points_to_view = points_ss.str();
    return points_to_view;
}
