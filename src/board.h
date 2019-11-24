#ifndef BOARD_H
#define BOARD_H

#include <2D/sprite.h>
#include <2D/physics/rectangle_hitbox.h>


class Board {

    public:

        undicht::Sprite m_sprite;
        undicht::RectangleHitbox m_hitbox;

        /** moving based on the user input */
        virtual void update();

        Board();
        virtual ~Board();


};

#endif // BOARD_H
