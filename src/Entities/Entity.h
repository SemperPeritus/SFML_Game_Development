#ifndef SFML_GAME_DEVELOPMENT_ENTITY_H
#define SFML_GAME_DEVELOPMENT_ENTITY_H

#include <SFML/Graphics.hpp>

#include "SceneNode.h"


class Entity : public SceneNode {
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

private:
    sf::Vector2f velocity;

private:
    virtual void updateCurrent(sf::Time deltaTime);
};

#endif
