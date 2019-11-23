#include <engine.h>
#include <window/graphics_context.h>
#include <string>
#include <core/core.h>
#include <vector>

#include <2D/sprite_renderer.h>
#include <file_loading/image/image_reader.h>
#include <2D/physics/physics_engine.h>
#include <2D/physics/rectangle_hitbox.h>

using namespace undicht;
using namespace undicht::graphics;
using namespace undicht::window;
using namespace undicht::core;

// linux
/*std::string window_lib = "engine/undicht/core/implementation/window/glfw/libwindow_glfw.so";
std::string graphics_lib = "engine/undicht/core/implementation/graphics/opengl_33/libvideo_opengl_33.so";
std::string audio_lib = "engine/undicht/core/implementation/audio/openal/libaudio_openal.so";*/

// windows
std::string window_lib = "engine/undicht/core/implementation/window/glfw/window_glfw.dll";
std::string graphics_lib = "engine/undicht/core/implementation/graphics/opengl_33/video_opengl_33.dll";
std::string audio_lib = "engine/undicht/core/implementation/audio/openal/audio_openal.dll";


int main() {

    Window* window;
    GraphicsContext* context;

    Core::setLibraryPaths(window_lib, graphics_lib, audio_lib);

    Engine::initialize(window, context);
    window->setSize(800, 600);


    {
        ImageReader image_reader;

        Sprite board;
        image_reader.loadImage(board, "res/board.png");
        board.setScale(glm::vec2(0.22, -0.05));
        board.setPosition(glm::vec3(0, -0.8, 0));

        Sprite background;
        image_reader.loadImage(background, "res/background.png");
        background.setUvScale(glm::vec2(10, -15));

        Sprite ball;
        image_reader.loadImage(ball, "res/ball.png");
        ball.setScale(glm::vec2(0.03, -0.04));

        // creating a wall of bricks to break
        Sprite brick;
        image_reader.loadImage(brick, "res/brick.png");
        brick.setScale(glm::vec2(0.08, -0.04));
        brick.setPosition(glm::vec3(0,0.5,0));

        /*std::vector<Sprite> bricks;

        for(int y = 0; y < 4; y++) {
            for(int x = 0; x < 11; x++) {
                bricks.push_back(brick);
                bricks.back().setPosition(glm::vec3(0.16 * x - 0.8, -0.08 * y + 0.76, 0));
            }
        }*/

        SpriteRenderer renderer;

        glm::vec3 ball_speed(0,0.01,0);


        while(!window->shouldClose()) {

            // drawing
            renderer.draw(background);
            renderer.draw(board);
            renderer.draw(ball);

            /*for(Sprite& s : bricks) {
                renderer.draw(s);
            }*/
            renderer.draw(brick);

            // doing physics stuff (what it could look like)
            /* Hitbox ball_hitbox;
            Hitbox brick_hitbox;

            CollisionReport ball_brick_collision;

            MovementPath ball_path;

            float time_offset = 0;


            do {

                ball_brick_collision = PhysicEngine::createCollisionReport(brick_hitbox, ball_hitbox, time_offset);

                if(ball_brick_collision)) {

                    time_offset = ball_brick_collision.getTimeToCollision;

                    // adding the collisions consequences to the movement path
                    ball_path.addMovement(PhysicsEngine::calcMovement(ball_hitbox, ball_brick_collision));

                } else {

                    break;
                }

            } while(time_offset <= 0.016)

            // moving the ball

            ball_hitbox.setPosition(ball_path.getEndPosition()); */

            // what the first prototype of the physics looks like
            RectangleHitbox ball_box;
            RectangleHitbox brick_box;
            RectangleHitbox board_box;

            ball_box.m_position = glm::vec2(ball.getPosition().x, ball.getPosition().y);
            ball_box.m_size = ball.getScale();
            ball_box.m_speed = glm::vec2(ball_speed.x, ball_speed.y);

            brick_box.m_position = glm::vec2(brick.getPosition().x, brick.getPosition().y);
            brick_box.m_size = brick.getScale();

            board_box.m_position = glm::vec2(board.getPosition().x, board.getPosition().y);
            board_box.m_size = board.getScale();

            Collision2D collision;
            collision = PhysicsEngine::testCollision(ball_box, brick_box);

            if(collision.getCollisionTime() < 0.02) {
                ball_speed *= -1;
            }

            collision = PhysicsEngine::testCollision(ball_box, board_box);

            if(collision.getCollisionTime() < 0.02) {
                ball_speed *= -1;
            }

            // updating the balls position
            ball.m_position += ball_speed;



            // showing the stuff on the screen
            context->swapBuffers();
            window->update();
        }


    }

    Engine::terminate(window, context);


    return 0;
}
