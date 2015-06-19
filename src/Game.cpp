#include "Game.h"


const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::PlayerSpeed = 100.f;


Game::Game(): window(sf::VideoMode(640, 480), "SFML Game Development"),
              textures("img/textures/"), fonts("fonts/") {
    initVariables();
    loadTextures();
    loadFonts();
    initTexts();
}


inline void Game::initVariables() {
    width = window.getSize().x;
    height = window.getSize().y;

    shouldExit = false;
    exitCode = EXIT_SUCCESS;

    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
}


inline void Game::loadTextures() {
    try {
        textures.load(Textures::Airplane, "eagle.png");
        textures.get(Textures::Airplane).setSmooth(true);
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


inline void Game::loadFonts() {
    fonts.load(Fonts::Sansation, "sansation.ttf");

    sansation = fonts.get(Fonts::Sansation);
}


inline void Game::initTexts() {
    psCounters.setFont(sansation);
    psCounters.setColor(sf::Color::White);
    psCounters.setCharacterSize(24);
    psCounters.setStyle(sf::Text::Bold);
    psCounters.setString("120\n60");
    psCounters.setPosition(width - 60, 5);
}


int Game::run() {
    // Delta time per frames
    sf::Clock clock;
    sf::Time deltaTime = sf::Time::Zero;
    // PS counters
    int framesPerTime = 0;
    int updatesPerTime = 0;
    sf::Int64 renderTime = 0;
    sf::Int64 updateTime = 0;

    // Game loop
    while (window.isOpen() && !shouldExit) {
        // Delta time per frames
        deltaTime += clock.restart();
        updateTime += deltaTime.asMicroseconds();
        updatesPerTime++;

        // Updating game states
        while (deltaTime > TimePerFrame) {
            // PS counters
            renderTime += deltaTime.asMicroseconds();
            framesPerTime++;
            // Updating states
            deltaTime -= TimePerFrame;
            processEvent();
            update(TimePerFrame);
        }

        // PS counters
        if (updatesPerTime >= 10 && framesPerTime >= 10) {
            psCounters.setString(std::to_string(updatesPerTime * 1000000 / updateTime) + "\n" +
                                         std::to_string(framesPerTime * 1000000 / renderTime));
            updatesPerTime = 0;
            framesPerTime = 0;
            updateTime = 0;
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

    window.draw(psCounters);

    window.display();
}


void Game::clearUp() {
    if (window.isOpen())
        window.close();
}
