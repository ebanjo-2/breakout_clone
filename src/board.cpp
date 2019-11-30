#include "board.h"

#include <core/types.h>

using namespace undicht::window;
using namespace undicht::core;

Board::Board()
{
    //ctor
}

Board::~Board()
{
    //dtor
}

void Board::update() {


    if(m_input->getKeyState(UND_KEY_A) == UND_KEY_PRESSED) {
        setPosition(getPosition() - glm::vec2(0.02, 0));
    }

    if(m_input->getKeyState(UND_KEY_D) == UND_KEY_PRESSED) {
        setPosition(getPosition() + glm::vec2(0.02, 0));
    }

}
