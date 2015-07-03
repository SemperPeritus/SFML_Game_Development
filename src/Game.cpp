#include "Game.h"

#include <iostream>


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
// const float Game::PlayerSpeed = 100.f;


Game::Game(): window(sf::VideoMode(640, 480), "SFML Game Development"),
              fonts("fonts/"), world(window) {
    initVariables();
    loadFonts();
    initTexts();
}


inline void Game::initVariables() {
    width = window.getSize().x;
    height = window.getSize().y;

    shouldExit = false;
    exitCode = EXIT_SUCCESS;
}


inline void Game::loadFonts() {
    fonts.load(Fonts::Sansation, "sansation.ttf");

    sansation = fonts.get(Fonts::Sansation);
}


inline void Game::initTexts() {
    fpsCounter.setFont(sansation);
    fpsCounter.setColor(sf::Color::White);
    fpsCounter.setCharacterSize(24);
    fpsCounter.setStyle(sf::Text::Bold);
    fpsCounter.setString(std::to_string(1000000 / TimePerFrame.asMicroseconds()));
    fpsCounter.setPosition(width - 60, 5);
}


int Game::run() {
    // Delta time per frames
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Time deltaTime = sf::Time::Zero;
    // FPS counter
    int framesPerTime = 0;
    sf::Int64 renderTime = 0;

    // Game loop
    while (window.isOpen() && !shouldExit) {
        // Delta time per frames
        elapsedTime = clock.restart();
        deltaTime += elapsedTime;

        // Updating game states
        while (deltaTime > TimePerFrame) {
            deltaTime -= TimePerFrame;
            processEvent();
            update(TimePerFrame);
        }

        // FPS Counter
        renderTime += elapsedTime.asMicroseconds();
        framesPerTime++;
        if (renderTime > 1000000 && framesPerTime > 0) {
            sf::Uint64 fps = (sf::Uint64) (framesPerTime) * 1000000 / renderTime;
            if (fps >= 60)
                fpsCounter.setColor(sf::Color::White);
            else if (fps >= 24)
                fpsCounter.setColor(sf::Color::Yellow);
            else
                fpsCounter.setColor(sf::Color::Red);
            fpsCounter.setString(std::to_string(fps));
            framesPerTime = 0;
            renderTime = 0;
        }

        // Rendering
        render();
    }

    clearUp();

    return exitCode;
}


void Game::processEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}


void Game::update(sf::Time elapsedTime) {
    world.update(elapsedTime);
}


void Game::render() {
    window.clear();

    window.clear();
    world.draw();

    window.setView(window.getDefaultView());

    window.draw(fpsCounter);

    window.display();
}


void Game::clearUp() {
    if (window.isOpen())
        window.close();
}


void Game::exit() {
    exitCode = EXIT_FAILURE;
    shouldExit = true;
    clearUp();
}
