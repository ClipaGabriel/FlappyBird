#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
#include "obstacles.h"
#include "player.h"
using namespace std;

Obstacles::Obstacles(float xx)
{
    x = xx;
}

int Obstacles::load_file()
{
    if (!texture_obstacleup.loadFromFile("images/obstacleup.png"))
        return -1;
    obstacle_up.setTexture(texture_obstacleup);

    if (!texture_obstacledown.loadFromFile("images/obstacledown.png"))
        return -1;
    obstacle_down.setTexture(texture_obstacledown);
    return 1;
}

void Obstacles::rand_obstacles()
{
    y_up = (std::rand() % (15+free_space)) - (55+free_space);
    y_down = y_up + obstacle_len + free_space;

}
void Obstacles::move_obstacles()
{
    x-=speed;
    obstacle_up.setPosition(x, y_up);
    obstacle_down.setPosition(x, y_down);
}

