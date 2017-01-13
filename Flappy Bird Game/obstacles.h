#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
using namespace std;
class Player;
class Obstacles: public sf::Transformable
{
public:
    sf::Texture texture_obstacledown;
    sf::Texture texture_obstacleup;
    sf::Sprite obstacle_down;
    sf::Sprite obstacle_up;
    int free_space = 150; 
    float x = 800;
    float y_up = 100;
    float y_down = 100;
    float obstacle_len = 300;
    float obstacle_width = 60;
    float speed = 2.5; 

	Obstacles(float xx);

    int load_file(); 

    void rand_obstacles(); 

    void move_obstacles(); 


};
