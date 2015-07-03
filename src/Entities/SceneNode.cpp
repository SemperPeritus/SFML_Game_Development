#include "SceneNode.h"

#include <cassert>


SceneNode::SceneNode() : children(), parent(nullptr) {
}


void SceneNode::attachChild(SceneNode::Ptr child) {
    child->parent = this;
    children.push_back(std::move(child));
}


SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
    auto found = std::find_if(children.begin(), children.end(), [&] (Ptr &p) -> bool {return p.get() == &node;});
#pragma clang diagnostic pop
    assert(found != children.end());
    Ptr result = std::move(*found);
    result->parent = nullptr;
    children.erase(found);
    return result;
}


void SceneNode::update(sf::Time deltaTime) {
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}


void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}


void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
}


void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const Ptr &child : children)
        child->draw(target, states);
}


void SceneNode::updateCurrent(sf::Time deltaTime) {
}


void SceneNode::updateChildren(sf::Time deltaTime) {
    for (Ptr &child : children)
        child->update(deltaTime);
}


sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode *node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;
    return transform;
}


sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}
