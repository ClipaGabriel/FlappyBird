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
#include "score.h"
#include "game.h"
using namespace std;



Game::Game()
{
    state = END;
    if (player.load_file()!= 1)
        return ;
    if (!font.loadFromFile("fonts/flappy.ttf"))
        return ;
    if (!background.loadFromFile("images/background.png"))
        return ;
    if (!floor.loadFromFile("images/floor.png"))
        return ;
    if (scores.import_file() != 1)
        return ;
    window.create(sf::VideoMode(480, 640), "Flappy Bird!", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    sounds = true;
    state = MENU;
}

void Game::runGame()
{
    while (state != END)
    {
        switch (state)
        {
        case MENU:
            menu();
            break;

        case GAME:
            single();
            break;

        case GAME_OVER:
            state = GAME;
            single();
            break;

        case SCORE:
            score();
            break;

        case OPTIONS:
            options();
            break;

        case END:
            break;
        }
    }
}

void Game::menu()
{
	background_sprite.setTexture(background);
	background_sprite.setPosition(0, 0);
	floor_sprite.setTexture(floor);
	floor_sprite.setPosition(0, 550);
	if (!start.loadFromFile("images/start.png"))
		return;
	if (!logo.loadFromFile("images/logo.png"))
		return;
	if (!results.loadFromFile("images/score.png"))
		return;
	if (!settings.loadFromFile("images/options.png"))
		return;
	if (!exit.loadFromFile("images/exit.png"))
		return;

	logosprite.setTexture(logo);
	startsprite.setTexture(start);
	resultssprite.setTexture(results);
	settingssprite.setTexture(settings);
	exitsprite.setTexture(exit);


    logosprite.setPosition(480/2-logosprite.getGlobalBounds().width/2, 20);



    const int buttons = 4;

    sf::Text buttons_text[buttons];

    string str[] = {"Play", "Score", "Options", "Exit"};
    for (int i = 0; i < buttons; i++)
    {
        //buttons_text[i].setFont(font);
        //buttons_text[i].setCharacterSize(45);

       // buttons_text[i].setString(str[i]);
        buttons_text[i].setPosition(480/2-buttons_text[i].getGlobalBounds().width/2, 150+i*80);
    }
	startsprite.setPosition(480 / 2 - startsprite.getGlobalBounds().width / 2, 150);
	resultssprite.setPosition(480 / 2 - resultssprite.getGlobalBounds().width / 2, 230);
	settingssprite.setPosition(480 / 2 - settingssprite.getGlobalBounds().width / 2, 310);
	exitsprite.setPosition(480 / 2 - exitsprite.getGlobalBounds().width / 2, 380);
    while (state == MENU)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
                    event.key.code == sf::Keyboard::Escape)
                state = END;


            else if (startsprite.getGlobalBounds().contains(mouse)&&
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = GAME;
            }
            else if (resultssprite.getGlobalBounds().contains(mouse)&&
                     (event.type == sf::Event::MouseButtonReleased) &&
                     (event.key.code == sf::Mouse::Left))
            {
                state = SCORE;
            }

            else if (settingssprite.getGlobalBounds().contains(mouse)&&
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = OPTIONS;
            }

            else if (exitsprite.getGlobalBounds().contains(mouse)&&
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = END;
            }
        }
        window.clear();

        for (int i = 0; i<buttons; i++)
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
                buttons_text[i].setFillColor(sf::Color::Yellow);
            else
                buttons_text[i].setFillColor(sf::Color::Black);
        }
		window.draw(background_sprite);
		window.draw(floor_sprite);
		window.draw(logosprite);
		window.draw(startsprite);
		window.draw(resultssprite);
		window.draw(settingssprite);
		window.draw(exitsprite);
        for (int i = 0; i<buttons; i++)
        {
            window.draw(buttons_text[i]);
        }
        window.display();
    }
}

void Game::single()
{
	player.reset_player();
    bool colision = false;
	Obstacles obstacles(800);
	Obstacles obstacles2(1200);
    background_sprite.setTexture(background);
    background_sprite.setPosition(0,0);
    floor_sprite.setTexture(floor);
    floor_sprite.setPosition(0, 550);
    obstacles.rand_obstacles();
    obstacles2.rand_obstacles();
    text.setFont(font);
    error.setFont(font);
    text.setPosition(240, 50);
    error.setPosition(65, 200);
    error.setCharacterSize(30);
    error.setFillColor(sf::Color::Red);
    if (obstacles.load_file()!= 1)
        state = END;
    if (obstacles2.load_file()!= 1)
        state = END;
    if (scores.import_file() != 1)
        state = END;

    while (state == GAME)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (player.speed != 0)
                {
					player.y-=40;
                    if (sounds) player.fly.play();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && player.speed == 0)
            {
                state = GAME_OVER;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && player.speed == 0)
            {
                state = MENU;
            }

        }
        if (player.over_obstacles(obstacles))
        {
            if (sounds) player.get_point.play();
        }
        if (player.over_obstacles(obstacles2))
        {
            if (sounds) player.get_point.play();
        }
        if (player.detect_collision(obstacles) == true ||
			player.detect_collision(obstacles2) == true)
        {
			player.speed = 0;
            obstacles.speed = 0;
            obstacles2.speed = 0;
            if (!colision)
            {
                colision = true;
                if (sounds) player.die.play();
            }
            if (scores.check(player.points))
            {
                scores.save();
            }
            error.setString("You lost! Earned points: " + player.return_points() + "\n" +
                            "Your best score: " + scores.return_points() + " points" + "\n");
        }
        else
        {
            error.setString("");
        }
        text.setString(player.return_points());
		player.move_player();
        obstacles.move_obstacles();
        obstacles2.move_obstacles();
        window.clear();
        window.draw(background_sprite);
        window.draw(obstacles.obstacle_up);
        window.draw(obstacles.obstacle_down);
        window.draw(obstacles2.obstacle_up);
        window.draw(obstacles2.obstacle_down);
        window.draw(floor_sprite);
        window.draw(text);
        window.draw(player.player);
        window.draw(error);
        window.display();
    }
}

void Game::score()
{
    sf::Text title("Score info", font, 80);
    title.setStyle(sf::Text::Bold);

    title.setPosition(480/2-title.getGlobalBounds().width/2, 20);

    const int buttons = 2;

    sf::Text buttons_text[buttons];

    string str[] = {"Your best score = " + scores.return_points(), "Return to menu"};
    for (int i = 0; i < buttons; i++)
    {
        buttons_text[i].setFont(font);
        buttons_text[i].setCharacterSize(35);

        buttons_text[i].setString(str[i]);
        buttons_text[i].setPosition(480/2-buttons_text[i].getGlobalBounds().width/2, 250+i*120);
    }

    while (state == SCORE)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
                    event.key.code == sf::Keyboard::Escape)
                state = MENU;

            else if (buttons_text[1].getGlobalBounds().contains(mouse)&&
                     (event.type == sf::Event::MouseButtonReleased) &&
                     (event.key.code == sf::Mouse::Left))
            {
                state = MENU;
            }
        }
        window.clear();

        for (int i = 0; i<buttons; i++)
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
                buttons_text[i].setFillColor(sf::Color::Yellow);
            else
                buttons_text[i].setFillColor(sf::Color::Black);
        }
		window.draw(background_sprite);
		window.draw(floor_sprite);
        for (int i = 0; i<buttons; i++)
        {
            window.draw(buttons_text[i]);
        }
        window.draw(title);
        window.display();
    }
}

void Game::options()
{
    sf::Text title("Options", font, 80);
    title.setStyle(sf::Text::Bold);

    sf::Texture playertexture;
    sf::Sprite yellow_player;
    if (!playertexture.loadFromFile("images/flappy.png"))
    {
        state = END;
        return ;
    }
    yellow_player.setTexture(playertexture);

    sf::Texture playertexture1;
    sf::Sprite blue_player;
    if (!playertexture1.loadFromFile("images/flappy2.png"))
    {
        state = END;
        return ;
    }
    blue_player.setTexture(playertexture1);

    yellow_player.setPosition(170, 250);
    blue_player.setPosition(620, 250);

    title.setPosition(480/2-title.getGlobalBounds().width/2, 20);

    const int buttons = 4; // how much buttons

    sf::Text buttons_text[buttons];

    string str[] = {"Yellow bird" , "Blue bird", "Return to menu", "Sounds: ON"};
    for (int i = 0; i < buttons; i++)
    {
        buttons_text[i].setFont(font);
        buttons_text[i].setCharacterSize(65);

        buttons_text[i].setString(str[i]);

    }
    buttons_text[0].setPosition(50, 150);
    buttons_text[1].setPosition(500, 150);
    buttons_text[2].setPosition(480/2-buttons_text[2].getGlobalBounds().width/2, 490);
    buttons_text[3].setPosition(250, 350);

    if (sounds)
    {
        buttons_text[3].setFillColor(sf::Color::Green);
        buttons_text[3].setString("Sounds: ON");
    }
    else
    {
        buttons_text[3].setFillColor(sf::Color::Red);
        buttons_text[3].setString("Sounds: OFF");
    }



    while (state == OPTIONS)
    {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed&&
            event.key.code == sf::Keyboard::Escape)
                state = MENU;

            else if ((buttons_text[0].getGlobalBounds().contains(mouse) || yellow_player.getGlobalBounds().contains(mouse)) &&
            (event.type == sf::Event::MouseButtonReleased) &&
            (event.key.code == sf::Mouse::Left))
            {
				player.player.setTexture(player.playertexture);

            }

            else if ((buttons_text[1].getGlobalBounds().contains(mouse) || blue_player.getGlobalBounds().contains(mouse)) &&
                     (event.type == sf::Event::MouseButtonReleased) &&
                     (event.key.code == sf::Mouse::Left))

            {
				player.player.setTexture(player.playertexture1);
            }
            else if ((buttons_text[2].getGlobalBounds().contains(mouse)) &&
                     (event.type == sf::Event::MouseButtonReleased) &&
                     (event.key.code == sf::Mouse::Left))
            {
                state = MENU;
            }

            else if ((buttons_text[3].getGlobalBounds().contains(mouse)) &&
                     event.type == sf::Event::MouseButtonReleased &&
                     event.key.code == sf::Mouse::Left)
            {
                if (sounds)
                {
                    buttons_text[3].setString("Sounds: OFF");
                    buttons_text[3].setFillColor(sf::Color::Red);
                    sounds = false;
                }

                else
                {
                    buttons_text[3].setString("Sounds: ON");
                    buttons_text[3].setFillColor(sf::Color::Green);
                    sounds = true;
                }

            }

        }
        window.clear();

        for (int i = 0; i<buttons - 1; i++) // -1 because the sounds button is collored above
        {
            if (buttons_text[i].getGlobalBounds().contains(mouse))
                buttons_text[i].setFillColor(sf::Color::Yellow);
            else
                buttons_text[i].setFillColor(sf::Color::Black);
        }
		window.draw(background_sprite);
		window.draw(floor_sprite);
        for (int i = 0; i<buttons; i++)
        {
            window.draw(buttons_text[i]);
        }
        window.draw(title);
        window.draw(yellow_player);
        window.draw(blue_player);
        window.display();
    }
}

