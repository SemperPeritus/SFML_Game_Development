#ifndef SFML_GAME_DEVELOPMENT_SCENENODE_H
#define SFML_GAME_DEVELOPMENT_SCENENODE_H

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Managers/ResourceIdentifiers.h"


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    typedef std::unique_ptr<SceneNode> Ptr;

public:
    SceneNode();
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode & node);
    void update(sf::Time deltaTime);
    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time deltaTime);
    void updateChildren(sf::Time deltaTime);

private:
    std::vector<Ptr> children;
    SceneNode * parent;
};

#endif
