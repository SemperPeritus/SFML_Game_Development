#include "Aircraft.h"


Textures::ID toTextureID(Aircraft::Type type) {
    switch (type) {
        case Aircraft::Eagle:
            return Textures::Eagle;
        case Aircraft::Raptor:
            return Textures::Raptor;
        default:
            throw std::runtime_error("Texture don't exists for " + type);
    }
}


Aircraft::Aircraft(Aircraft::Type type, const TextureHolder &textures) : type(type),
                                                                         sprite(textures.get(toTextureID(type))) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void Aircraft::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
