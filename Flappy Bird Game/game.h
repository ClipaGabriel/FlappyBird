#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
using namespace std;


class Game:public sf::Transformable
{
public:
    sf::RenderWindow window;
    enum GameState {MENU, GAME, SCORE, OPTIONS, GAME_OVER, END};
    GameState state;
	Score scores;
	Player player;
    sf::Font font;
    sf::Text text;
    sf::Text error;
	sf::Texture logo;
	sf::Sprite logosprite;
	sf::Texture start;
	sf::Sprite startsprite;
	sf::Texture results;
	sf::Sprite resultssprite;
	sf::Texture settings;
	sf::Sprite settingssprite;
	sf::Texture exit;
	sf::Sprite exitsprite;
    sf::Texture background;
    sf::Texture floor;
    sf::Sprite background_sprite;
    sf::Sprite floor_sprite;
    bool sounds;

    Game();

    void runGame();

    void menu();

    void single();

    void score();

    void options();

};
