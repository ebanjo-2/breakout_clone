#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm/glm.hpp>
#include <2D/sprite.h>
#include <2D/physics/rectangle_hitbox.h>


class GameObject {
    public:

        undicht::Sprite m_sprite;
        undicht::RectangleHitbox m_hitbox;

        virtual void setPosition(const glm::vec2& pos);
        virtual glm::vec2 getPosition();

        virtual void setSpeed(const glm::vec2& speed);
        virtual glm::vec2 getSpeed();

        virtual void setScale(const glm::vec2& scale);
        virtual glm::vec2 getScale();

        /// moves the object a step the size of speed * time
        virtual void update(float time);



        GameObject();
        virtual ~GameObject();

};

#endif // GAMEOBJECT_H
