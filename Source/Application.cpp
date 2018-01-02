#include "Application.h"

#include "ScreenBuffer.h"
#include "ImageBuffer.h"
#include "Util/Shader.h"
#include "ConfigManager.h"

#include <stdexcept>
#include <GLFW/glfw3.h>
#include <iostream>


void initiate_png_mode(std::shared_ptr<PixelBufferBase>& pixel_buffer,
                       std::shared_ptr<Screen<int>>& screen) {
    std::cout << "\nPlease enter the location to where you want the scene to be drawn\nExample: To draw to a file named "
            "scene.png type scene.png" << std::endl;

    std::string src;
    while (!(std::cin >> src))
        ;

    pixel_buffer = std::make_shared<ImageBuffer>(screen, src);
}

void initiate_opengl_mode(std::shared_ptr<PixelBufferBase>& pixel_buffer,
                          std::shared_ptr<Screen<int>>& screen) {
    // Initialise pointer to a draw buffer
    pixel_buffer = std::make_shared<ScreenBuffer>(screen, "Shaders/vertex.vert", "Shaders/fragment.frag");
}

Application::Application() {
    std::cout << "Running raymarcher created by Balajanovski..." << std::endl;

    m_screen = std::make_shared<Screen<int>>(0, ConfigManager::instance().get_screen_width(),
                                             0, ConfigManager::instance().get_screen_height());
    m_scene =  std::make_shared<Scene>();

#if defined(GLFW_FOUND) && defined(OPENGL_FOUND) && defined(PNG_FOUND)
    std::cout << "\nWould you like to draw the scene to a window or an image?\n"
              << "Type W for window or I for image" << std::endl;

    char response;
    while (!(std::cin >> response))
        ;

    switch (response) {
        case 'W' : case 'w' :
        {
            initiate_opengl_mode(m_stream, m_screen);
        }
            break;

        case 'I' : case 'i' :
        {
            initiate_png_mode(m_stream, m_screen);
        }
            break;

        default:
        {
            std::cout << "\nInvalid response: Shutting down" << std::endl;
            exit(EXIT_FAILURE);
        }
            break;
    }

#elif defined(GLFW_FOUND) && defined(OPENGL_FOUND)
    std::cout << "Warning: libPNG not found, initiating OpenGL mode" << std::endl;
    initiate_opengl_mode(m_stream, m_screen);
#elif defined(PNG_FOUND)
    std::cout << "Warning: GLFW / OpenGL not found, initiating libPNG mode" << std::endl;
    initiate_png_mode(m_stream, m_screen);
#else
    std::cout << "Fatal Error: Neither libPNG or GLFW were found\nShutting down..." << std::endl;
    exit(EXIT_FAILURE);
#endif

    m_raymarcher = std::make_shared<Raymarcher>(m_scene, m_stream, m_screen);
}

Application::~Application() {
    glfwTerminate();
}


void Application::run_loop() {

    m_raymarcher->calculate_frame();
    m_stream->flush();

    std::cout << "Closing down..." << std::endl;
}