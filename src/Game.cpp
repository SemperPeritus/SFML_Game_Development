#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::PlayerSpeed = 100.f;


Game::Game(): window(sf::VideoMode(640, 480), "SFML Game Development"), player(),texture() {
    initVariables();

    if (!texture.loadFromFile("img/sprites/eagle.png"))
        window.close();
    player.setTexture(texture);
    player.setPosition(100.f, 100.f);
}


void Game::initVariables() {
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
}


void Game::run() {
    sf::Clock clock;
    sf::Time deltaTime = sf::Time::Zero;

    while (window.isOpen()) {
        deltaTime += clock.restart();
        while (deltaTime > TimePerFrame) {
            deltaTime -= TimePerFrame;
            processEvent();
            update(TimePerFrame);
        }
        render();
    }
}


void Game::processEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::W:
            isMovingUp = isPressed;
            break;
        case sf::Keyboard::S:
            isMovingDown = isPressed;
            break;
        case sf::Keyboard::A:
            isMovingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            isMovingRight = isPressed;
            break;
        default:
            break;
    }
}


void Game::update(sf::Time elapsedTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= PlayerSpeed;
    if (isMovingDown)
        movement.y += PlayerSpeed;
    if (isMovingLeft)
        movement.x -= PlayerSpeed;
    if (isMovingRight)
        movement.x += PlayerSpeed;
    player.move(movement * elapsedTime.asSeconds());
}


void Game::render() {
    window.clear();
    window.draw(player);
    window.display();
}
