#ifndef BRICK_H
#define BRICK_H

#include <game_object.h>

class Brick : public GameObject {
    public:


        bool m_destroyed = false;

        Brick();
        virtual ~Brick();
};

#endif // BRICK_H
