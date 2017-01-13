#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
#include "player.h"
#include "obstacles.h"
using namespace std;

int Player::load_file()
{
    if (!playertexture.loadFromFile("images/flappy1.png"))
        return -1;

	player.setTexture(playertexture);

    if (!playertexture1.loadFromFile("images/flappy2.png"))
        return -1;

    if (!get_point_buffer.loadFromFile("sounds/points.ogg"))
        return -1;

    get_point.setBuffer(get_point_buffer);

    if (!fly_buffer.loadFromFile("sounds/fly.ogg"))
        return -1;

    fly.setBuffer(fly_buffer);

    if (!die_buffer.loadFromFile("sounds/die.ogg"))
        return -1;

    die.setBuffer(die_buffer);

    return 1;
}

void Player::move_player()
{
    y+=speed;
	player.setPosition(x, y);
}



string Player::return_points()
{
    std::stringstream points_ss;
    points_ss << points;
    std::string points_to_view = points_ss.str();
    return points_to_view;
}

bool Player::detect_collision(Obstacles obstacles)
{

    if ((y < obstacles.y_up+obstacles.obstacle_len && y > obstacles.y_up) ||
            (y < obstacles.y_down+obstacles.obstacle_len && y > obstacles.y_down) ||
            (y+length < obstacles.y_up+obstacles.obstacle_len && y + length > obstacles.y_up) ||
            (y+length < obstacles.y_down+obstacles.obstacle_len && y + length > obstacles.y_down))
    {
        if (x + width > obstacles.x && x + width < obstacles.x + obstacles.obstacle_width)
            return true;

        if (y <= -40 || y >= 500)
            return true;
    }
    return false;
}

bool Player::over_obstacles(Obstacles &pipe)
{
    if (pipe.x <= -200)
    {
		points += 1;
        pipe.x = 500;
        pipe.rand_obstacles();
        return true;
    }

    else
    {
        return false;
    }
}

void Player::reset_player()
{
    speed = 3.5;
    y = 300;
    x = 30;
    length = 40;
    width = 30;
    points = 0;
}
