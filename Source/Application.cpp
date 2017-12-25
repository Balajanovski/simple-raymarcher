#include "Application.h"

#include "Util/Shader.h"

#include <stdexcept>

#include <glfw/glfw3.h>

#include <thread>


Application::Application() {
    m_screen = new Screen<int>(0, 1000, 0, 1000);
    m_camera = new Camera(Vec3f(0.0f, 0.0f, -1.0f));
    m_scene =  new Scene();
    m_stream = new Screen_Stream(m_screen, "Shaders/vertex.vert", "Shaders/fragment.frag");
    m_raymarcher = new Raymarcher(m_scene, m_camera, m_stream, m_screen);
}

Application::~Application() {
    glfwTerminate();

    delete m_raymarcher;
    delete m_stream;
    delete m_scene;
    delete m_camera;
    delete m_screen;
}


void Application::run_loop() {
/*
    m_raymarcher->calculate_frame();
    m_stream->flush();
    m_stream->swap_buffers();

    while (!m_stream->should_window_close()) {
        if(m_stream->key_pressed(GLFW_KEY_ESCAPE)) {
            m_stream->set_window_should_close(true);
        }
        m_stream->poll_events();
    }
*/

    // Game loop
    int last_ticks = 0,
            lag = 0;
    while (!m_stream->should_window_close()) {
        if(m_stream->key_pressed(GLFW_KEY_ESCAPE)) {
            m_stream->set_window_should_close(true);
        }
        if (m_stream->key_pressed(GLFW_KEY_W)) {
            m_camera->set_pos(m_camera->pos().set_z(m_camera->pos().z() + 0.02f));
        }

        int current_ticks = glfwGetTime();
        int elapsed = current_ticks - last_ticks;
        last_ticks = current_ticks;
        lag += elapsed;

        m_scene->iterate(glfwGetTime());
        m_raymarcher->calculate_frame();
        m_stream->flush();

        m_stream->swap_buffers();
        glfwPollEvents();
    }


}