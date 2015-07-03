#ifndef SFML_GAME_DEVELOPMENT_WORLD_H
#define SFML_GAME_DEVELOPMENT_WORLD_H


#include <SFML/Graphics/RenderWindow.hpp>

#include "Managers/ResourceIdentifiers.h"
#include "Entities/SceneNode.h"
#include "Entities/Aircraft.h"


class World {
public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time deltaTime);
    void draw();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer {
        Background,
        Air,
        count
    };

private:
    sf::RenderWindow &window;
    sf::View worldView;
    TextureHolder textures;
    SceneNode sceneGraph;
    std::array<SceneNode*, Layer::count> sceneLayers;
    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    float scrollSpeed;
    Aircraft *playerAircraft;
};

#endif
