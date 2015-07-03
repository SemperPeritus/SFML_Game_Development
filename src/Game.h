#ifndef SFML_GAME_DEVELOPMENT_GAME_H
#define SFML_GAME_DEVELOPMENT_GAME_H

#include <SFML/Graphics.hpp>

#include "Managers/ResourceIdentifiers.h"

#include "Entities/Aircraft.h"
#include "World.h"


class Game {
public:
    Game();
    int run();
    void exit();

private:
    sf::RenderWindow window;
    int width;
    int height;

    World world;

    sf::Font sansation;

    sf::Text fpsCounter;

    static const sf::Time TimePerFrame;
    // static const float PlayerSpeed;

    bool shouldExit;

    FontHolder fonts;

    int exitCode;

private:
    void initVariables();
    void loadFonts();
    void initTexts();

    void processEvent();
    void update(sf::Time deltaTime);
    void render();

    void clearUp();
};

#endif
