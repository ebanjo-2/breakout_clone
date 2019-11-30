#include "level.h"
#include <file_loading/image/image_reader.h>
#include <2D/physics/physics_engine.h>
#include <2D/physics/collision.h>

const std::string board_res = "res/board.png";
const std::string ball_res = "res/ball.png";
const std::string brick_res = "res/brick.png";

const std::string background_res = "res/background.png";


using namespace undicht;


Level::Level() {
    //ctor
}

Level::~Level() {
    //dtor
}


void Level::init(undicht::window::KeyInputWatcher* input) {

    // loading all sprites
    ImageReader image_reader;
    Brick brick_prototype; // a sprite to load the brick texture to
    image_reader.loadImage(m_board.m_sprite, board_res);
    image_reader.loadImage(m_ball.m_sprite, ball_res);
    image_reader.loadImage(brick_prototype.m_sprite, brick_res);
    image_reader.loadImage(m_sprite, background_res);

    // making the backround texture repeat itself
    m_sprite.setUvScale(glm::vec2(10, -15));

    // setting all the default positions and scales of the levels objects
    m_board.setScale(glm::vec2(0.22f, -0.05f));
    m_board.setPosition(glm::vec2(0.0f, -0.8f));
    m_board.m_input = input;

    m_ball.setPosition(glm::vec2(0,0));
    m_ball.setScale(glm::vec2(0.03, -0.04));
    m_ball.setSpeed(glm::vec2(1,-1));

    brick_prototype.setScale(glm::vec2(0.08, -0.04));

    // setting the level scale
    setPosition(glm::vec2(0,0));
    setScale(glm::vec2(1.0f,1.0f));

    // creating a wall of bricks to break
    for(int y = 0; y < 4; y++) {
        for(int x = 0; x < 11; x++) {
            m_bricks.push_back(brick_prototype);
            m_bricks.back().setPosition(glm::vec2(0.16 * x - 0.8, -0.08 * y + 0.76));
        }
    }

}



void Level::update(float delta_time) {
    /** moving the board + ball */

    Collision2D c; // the object to hold data about collisions

    // testing for collision between ball + board
    c = PhysicsEngine::testCollision(m_ball.m_hitbox, m_board.m_hitbox);

    if(c.getCollisionTime() < 0.02) {
        m_ball.setSpeed(m_ball.getSpeed() * glm::vec2(1,-1)); // reverse y direction
    }

    // testing for collisions between ball + bricks
    for(Brick& b : m_bricks) {
        if(!b.m_destroyed) {
            c = PhysicsEngine::testCollision(m_ball.m_hitbox, b.m_hitbox);
            if(c.getCollisionTime() < 0.02) {
                m_ball.setSpeed(m_ball.getSpeed() * glm::vec2(1,-1)); // more details would need to be known
                b.m_destroyed = true;
            }
        }
    }

    // testing for collisions between ball + level edges
    c = PhysicsEngine::testCollision(m_ball.m_hitbox, m_hitbox);

    if(c.getCollisionTime() < 0.02) {

        if(glm::length(m_ball.getPosition().y) > 0.9 ) {
            m_ball.setSpeed(m_ball.getSpeed() * glm::vec2( 1,-1));
        }

        if(glm::length(m_ball.getPosition().x) > 0.9 ) {
            m_ball.setSpeed(m_ball.getSpeed() * glm::vec2(-1, 1));
        }

    }

    // moving ball + board
    m_board.update();
    m_ball.update(delta_time);

}



std::vector<undicht::Sprite*> Level::getSprites() {
    /** @return all the sprites in the level */

    std::vector<undicht::Sprite*> sprites;

    sprites.push_back(&m_sprite); // the background should be drawn first

    sprites.push_back(&m_ball.m_sprite);
    sprites.push_back(&m_board.m_sprite);

    for(Brick& b : m_bricks) {
        if(!b.m_destroyed)
            sprites.push_back(&b.m_sprite);
    }

    return sprites;
}



bool Level::isFinished() {
    /** true if all blocks were broken */


    for(Brick& b : m_bricks){
        if(!b.m_destroyed) {

            return false;
        }
    }

    return true;
}

