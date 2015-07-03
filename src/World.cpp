#include "World.h"

#include "Entities/SpriteNode.h"


World::World(sf::RenderWindow &window) : window(window), worldView(window.getDefaultView()), textures("img/textures/"),
                                         worldBounds(0.f, 0.f, worldView.getSize().x, 2000.f),
                                         spawnPosition(worldView.getSize().x / 2.f, worldBounds.height -
                                                 worldView.getSize().y / 2.f),
                                         scrollSpeed(-50.f), playerAircraft(nullptr) {
    loadTextures();
    buildScene();
    worldView.setCenter(spawnPosition);
}


void World::loadTextures() {
    textures.load(Textures::Eagle, "eagle.png");
    textures.get(Textures::Eagle).setSmooth(true);
    textures.load(Textures::Raptor, "raptor.png");
    textures.load(Textures::Desert, "desert.png");
}


void World::buildScene() {
    // Initialize the different layers
    for (std::size_t i = 0; i < Layer::count; i++) {
        SceneNode::Ptr layer(new SceneNode());
        sceneLayers[i] = layer.get();
        sceneGraph.attachChild(std::move(layer));
    }

    // Prepare the title background
    sf::Texture &texture = textures.get(Textures::Desert);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
    sceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Add player's aircraft
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, textures));
    playerAircraft = leader.get();
    playerAircraft->setPosition(spawnPosition);
    playerAircraft->setVelocity(40.f, scrollSpeed);
    sceneLayers[Air]->attachChild(std::move(leader));

    // Add two escorting aircrafts, placed relatively to the main plane
    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, textures));
    leftEscort->setPosition(-80.f, 50.f);
    playerAircraft->attachChild(std::move(leftEscort));
    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, textures));
    rightEscort->setPosition(80.f, 50.f);
    playerAircraft->attachChild(std::move(rightEscort));
}


void World::update(sf::Time deltaTime) {
    worldView.move(0.f, scrollSpeed * deltaTime.asSeconds());

    sf::Vector2f position = playerAircraft->getPosition();
    sf::Vector2f velocity = playerAircraft->getVelocity();
    if (position.x <= worldBounds.left + 150 || position.x >= worldBounds.width - 150) {
        velocity.x = -velocity.x;
        playerAircraft->setVelocity(velocity);
    }

    sceneGraph.update(deltaTime);
}


void World::draw() {
    window.setView(worldView);
    window.draw(sceneGraph);
}
