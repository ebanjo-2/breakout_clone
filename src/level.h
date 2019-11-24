#ifndef LEVEL_H
#define LEVEL_H


#include <2D/sprite.h>

class Level {
    public:



        /** moving the board + ball */
        virtual void update();

        /** @return all the sprites in the level */
        virtual std::vector<undicht::Sprite*> getSprites();

        Level();
        virtual ~Level();


};



#endif // LEVEL_H
