#include <engine.h>
#include <window/graphics_context.h>
#include <string>
#include <core/core.h>

using namespace undicht;
//using namespace undicht::graphics;
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

        while(!window->shouldClose()){




            context->swapBuffers();
            window->update();
        }


    }

    Engine::terminate(window, context);


    return 0;
}
