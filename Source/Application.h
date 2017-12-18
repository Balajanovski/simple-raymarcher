#ifndef OPENGL_BOILERPLATE_APPLICATION_H
#define OPENGL_BOILERPLATE_APPLICATION_H

#include "Util/Shader.h"
#include "Pixel_Stream_Base.h"
#include "Screen_Stream.h"
#include "Raymarcher.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

class Application {
public:
    Application();
    ~Application();
    void run_loop();
private:

    std::shared_ptr<Screen_Stream> m_stream;
    std::shared_ptr<Raymarcher> m_raymarcher;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Screen<int>> m_screen;

    constexpr static int WINDOW_WIDTH = 800;
    constexpr static int WINDOW_HEIGHT = 600;
    constexpr static int MS_PER_UPDATE = 2;

};


#endif //OPENGL_BOILERPLATE_APPLICATION_H
