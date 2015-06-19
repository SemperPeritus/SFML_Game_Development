#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::PlayerSpeed = 100.f;


Game::Game(): window(sf::VideoMode(640, 480), "SFML Game Development"),
              textures("img/textures/") {
    initVariables();
    loadTextures();
}


void Game::initVariables() {
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;

    shouldExit = false;
    exitCode = EXIT_SUCCESS;
}


void Game::loadTextures() {
    try {
        textures.load(Textures::Airplane, "eagle.png");
        textures.load(Textures::Desert, "desert.png");
    }
    catch (std::runtime_error& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        exitCode = EXIT_FAILURE;
        shouldExit = true;
    }

    player = sf::Sprite(textures.get(Textures::Airplane));
    player.setPosition(200.f, 200.f);
    landscape = sf::Sprite(textures.get(Textures::Desert));
}


int Game::run() {
    sf::Clock clock;
    sf::Time deltaTime = sf::Time::Zero;

    // Game loop
    while (window.isOpen() && !shouldExit) {
        deltaTime += clock.restart();
        while (deltaTime > TimePerFrame) {
            deltaTime -= TimePerFrame;
            processEvent();
            update(TimePerFrame);
        }
        render();
    }

    clearUp();

    return exitCode;
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
    window.draw(landscape);
    window.draw(player);
    window.display();
}


void Game::clearUp() {
    if (window.isOpen())
        window.close();
}
