#include "Application.h"

#include "Util/Shader.h"

#include <stdexcept>

#include <glfw/glfw3.h>

#include <thread>


Application::Application() {
    m_screen = new Screen<int>(0, 1000, 0, 1000);
    m_scene =  new Scene();
    m_stream = new ScreenBuffer(m_screen, "Shaders/vertex.vert", "Shaders/fragment.frag");
    m_raymarcher = new Raymarcher(m_scene, m_stream, m_screen);
}

Application::~Application() {
    glfwTerminate();

    delete m_raymarcher;
    delete m_stream;
    delete m_scene;
    delete m_screen;
}


void Application::run_loop() {

    m_raymarcher->calculate_frame();
    m_stream->flush();
    m_stream->swap_buffers();

    while (!m_stream->should_window_close()) {
        if(m_stream->key_pressed(GLFW_KEY_ESCAPE)) {
            m_stream->set_window_should_close(true);
        }
        m_stream->poll_events();
    }


}