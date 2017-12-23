#include "Application.h"

#include "Util/Shader.h"

#include <stdexcept>



Application::Application() {
    m_screen = std::make_shared<Screen<int>>(0, 1000, 0, 1000);
    m_camera = std::make_shared<Camera>(Vec3f(0.0f, 0.0f, -1.0f));
    m_scene = std::make_shared<Scene>();
    m_stream = std::make_shared<Screen_Stream>(m_screen, "Shaders/vertex.vert", "Shaders/fragment.frag");
    m_raymarcher = std::make_shared<Raymarcher>(m_scene, m_camera, m_stream, m_screen);
}

Application::~Application() {
    glfwTerminate();
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

    /* Game loop
    int last_ticks = 0,
            lag = 0;
    while (!m_stream->should_window_close()) {
        if(m_stream->key_pressed(GLFW_KEY_ESCAPE)) {
            m_stream->set_window_should_close(true);
        }

        int current_ticks = glfwGetTime();
        int elapsed = current_ticks - last_ticks;
        last_ticks = current_ticks;
        lag += elapsed;

        // While the game is lagging
        //while (lag >= MS_PER_UPDATE) {

        //    lag -= MS_PER_UPDATE;
        //}

        m_raymarcher->calculate_frame();
        m_stream->flush();

        m_stream->swap_buffers();
        glfwPollEvents();
    }
     */

}