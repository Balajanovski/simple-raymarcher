#ifndef OPENGL_BOILERPLATE_APPLICATION_H
#define OPENGL_BOILERPLATE_APPLICATION_H

#include "Util/Shader.h"
#include "Pixel_Stream_Base.h"
#include "Screen_Stream.h"
#include "Raymarcher.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

#include <memory>
#include <string>

class Application {
public:
    Application();
    ~Application();
    void run_loop();
private:

    Screen_Stream* m_stream;
    Raymarcher* m_raymarcher;
    Scene* m_scene;
    Camera* m_camera;
    Screen<int>* m_screen;

    constexpr static int WINDOW_WIDTH  = 800;
    constexpr static int WINDOW_HEIGHT = 600;
    constexpr static int MS_PER_UPDATE = 2;
    constexpr static int THREAD_NUMBER = 32;
};


#endif //OPENGL_BOILERPLATE_APPLICATION_H
