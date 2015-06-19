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

namespace Fonts {
    enum ID {
        Sansation,
    };
}


class Game {
public:
    Game();
    int run();

private:
    sf::RenderWindow window;
    int width;
    int height;

    sf::Sprite player;
    sf::Sprite landscape;

    sf::Font sansation;

    sf::Text psCounters;

    static const sf::Time TimePerFrame;
    static const float PlayerSpeed;

    bool shouldExit;

    ResourceHolder<sf::Texture, Textures::ID> textures;
    ResourceHolder<sf::Font, Fonts::ID> fonts;

    int exitCode;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight;

    void initVariables();
    void loadTextures();
    void loadFonts();
    void initTexts();

    void processEvent();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

    void clearUp();
};

#endif
