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

        virtual void init(undicht::window::KeyInputWatcher* input);

        /** moving the board + ball */
        virtual void update(float time);

        /** @return all the sprites in the level */
        virtual std::vector<undicht::Sprite*> getSprites();

        /** true if all blocks were broken */
        bool isFinished();

        Level();
        virtual ~Level();


};



#endif // LEVEL_H
