#ifndef OPENGL_BOILERPLATE_APPLICATION_H
#define OPENGL_BOILERPLATE_APPLICATION_H

#include "Util/Shader.h"
#include "PixelBufferBase.h"
#include "Raymarcher.h"
#include "Screen.h"
#include "Scene.h"
#include "Camera.h"

#include <memory>
#include <string>

class Application {
public:
    Application();
    ~Application();
    void run_loop();
private:


    std::shared_ptr<Raymarcher> m_raymarcher;
    std::shared_ptr<PixelBufferBase> m_stream;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<Screen<int>> m_screen;
};


#endif //OPENGL_BOILERPLATE_APPLICATION_H
