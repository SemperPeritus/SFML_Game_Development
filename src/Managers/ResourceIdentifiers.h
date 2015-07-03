#ifndef SFML_GAME_DEVELOPMENT_RESOURCEIDENTIFIERS_H
#define SFML_GAME_DEVELOPMENT_RESOURCEIDENTIFIERS_H

#include <SFML/Graphics.hpp>

#include "ResourceHolder.h"


namespace Textures {
    enum ID {
        Eagle,
        Raptor,
        Desert,
    };
}

namespace Fonts {
    enum ID {
        Sansation,
    };
}


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;


#endif
