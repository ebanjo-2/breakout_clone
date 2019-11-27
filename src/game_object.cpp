#include "game_object.h"

GameObject::GameObject() {
    //ctor
}

GameObject::~GameObject() {
    //dtor
}


void GameObject::setPosition(const glm::vec2& pos) {

    m_sprite.setPosition(glm::vec3(pos, 0));
    m_hitbox.m_position = pos;
}


glm::vec2 GameObject::getPosition() {

    return m_hitbox.m_position;
}

void GameObject::setSpeed(const glm::vec2& speed) {

    m_hitbox.m_speed = speed;
}

glm::vec2 GameObject::getSpeed() {

    return m_hitbox.m_speed;
}

void GameObject::setScale(const glm::vec2& scale) {

    m_sprite.m_scale = scale;
    m_hitbox.m_size = scale;

}

glm::vec2 GameObject::getScale() {

    return m_hitbox.m_size;
}


void GameObject::update(float time) {
    /// moves the object a step the size of speed * time

    setPosition(getPosition() + getSpeed() * time);
}
