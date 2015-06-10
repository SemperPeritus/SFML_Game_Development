#ifndef SFML_GAME_DEVELOPMENT_GAME_H
#define SFML_GAME_DEVELOPMENT_GAME_H

#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>


class Game {

public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite player;

    static const sf::Time TimePerFrame;
    static const float PlayerSpeed;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight;

    void initVariables();

    void processEvent();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

};

#endif
