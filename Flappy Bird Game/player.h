#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
using namespace std;
class Obstacles;
class Player :public sf::Transformable
{
public:
    sf::SoundBuffer get_point_buffer;
    sf::SoundBuffer fly_buffer;
    sf::SoundBuffer die_buffer;
    sf::Texture playertexture;
    sf::Texture playertexture1;
    sf::Sprite player;
    sf::Sound get_point;
    sf::Sound fly;
    sf::Sound die;
    float y = 300;
    float x = 30;
    float length = 40;
    float width = 30;
    int points = 0;
    float speed = 3.5;

    int load_file();

    void move_player();

    string return_points();

    bool detect_collision(Obstacles obstacles);

    bool over_obstacles(Obstacles &pipe);

    void reset_player();


};
