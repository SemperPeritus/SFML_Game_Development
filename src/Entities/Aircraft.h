#ifndef SFML_GAME_DEVELOPMENT_AIRCRAFT_H
#define SFML_GAME_DEVELOPMENT_AIRCRAFT_H

#include "Entity.h"


class Aircraft : public Entity {
public:
    enum Type {
        Eagle,
        Raptor,
    };


public:
    explicit Aircraft(Type type, const TextureHolder &textures);
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Type type;
    sf::Sprite sprite;
};

#endif
