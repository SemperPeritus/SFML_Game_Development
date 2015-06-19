#ifndef SFML_GAME_DEVELOPMENT_GAME_H
#define SFML_GAME_DEVELOPMENT_GAME_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "ResourceHolder.h"


namespace Textures {
    enum ID {
        Airplane,
        Desert,
    };
}


class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;

    sf::Sprite player;
    sf::Sprite landscape;

    static const sf::Time TimePerFrame;
    static const float PlayerSpeed;

    bool shouldExit;

    ResourceHolder<sf::Texture, Textures::ID> textures;

    int exitCode;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight;

    void initVariables();
    void loadTextures();

    void processEvent();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

    void clearUp();
};

#endif
