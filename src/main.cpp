#include <engine.h>
#include <window/graphics_context.h>
#include <string>
#include <core/core.h>
#include <vector>

#include <2D/sprite_renderer.h>
#include <file_loading/image/image_reader.h>
#include <2D/physics/physics_engine.h>
#include <2D/physics/rectangle_hitbox.h>
#include <level.h>

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

        SpriteRenderer renderer;

        KeyInputWatcher input;
        input.setWindow(window);

        Level level;
        level.init(&input);

        while(!window->shouldClose() && !level.isFinished()) {

            // game mechanics
            level.update(0.016);

            // drawing
            std::vector<Sprite*> sprites = level.getSprites();
            for(Sprite*& s : sprites) {
                renderer.draw(*s);
            }

            // showing the stuff on the screen
            context->swapBuffers();
            window->update();
        }

        std::cout << "Congratulations!!!! " << "\n";

    }



    Engine::terminate(window, context);


    return 0;
}
