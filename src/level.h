#ifndef LEVEL_H
#define LEVEL_H


#include <2D/sprite.h>
#include <board.h>
#include <brick.h>
#include <ball.h>
#include <vector>

class Level : private GameObject {
    public:

        Board m_board;
        Ball m_ball;
        std::vector<Brick> m_bricks;

        /** moving the board + ball */
        virtual void update(float time);

        virtual void init();


        /** @return all the sprites in the level */
        virtual std::vector<undicht::Sprite*> getSprites();

        Level();
        virtual ~Level();


};



#endif // LEVEL_H
