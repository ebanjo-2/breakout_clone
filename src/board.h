#ifndef BOARD_H
#define BOARD_H

#include <2D/sprite.h>
#include <2D/physics/rectangle_hitbox.h>
#include <game_object.h>
#include <window/key_input_watcher.h>


class Board : public GameObject {

    public:

        undicht::window::KeyInputWatcher* m_input;

        /** moving based on the user input */
        virtual void update();

        Board();
        virtual ~Board();


};

#endif // BOARD_H
