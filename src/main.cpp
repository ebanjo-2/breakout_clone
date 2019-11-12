#include <engine.h>
#include <window/graphics_context.h>
#include <string>
#include <core/core.h>
#include <vector>

#include <2D/sprite_renderer.h>
#include <file_loading/image/image_reader.h>

using namespace undicht;
using namespace undicht::graphics;
using namespace undicht::window;
using namespace undicht::core;

std::string window_lib = "engine/undicht/core/implementation/window/glfw/libwindow_glfw.so";
std::string graphics_lib = "engine/undicht/core/implementation/graphics/opengl_33/libvideo_opengl_33.so";
std::string audio_lib = "engine/undicht/core/implementation/audio/openal/libaudio_openal.so";

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
        board.setScale(glm::vec2(0.2, -0.05));
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

        std::vector<Sprite> bricks;

        for(int y = 0; y < 4; y++) {
            for(int x = 0; x < 11; x++) {
                bricks.push_back(brick);
                bricks.back().setPosition(glm::vec3(0.16 * x - 0.8, -0.08 * y + 0.76, 0));
            }
        }

        SpriteRenderer renderer;


        while(!window->shouldClose()) {

            // drawing
            renderer.draw(background);
            renderer.draw(board);
            renderer.draw(ball);

            for(Sprite& s : bricks) {
                renderer.draw(s);
            }

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

            // showing the stuff on the screen
            context->swapBuffers();
            window->update();
        }


    }

    Engine::terminate(window, context);


    return 0;
}
