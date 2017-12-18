// 
// Created by Balajanovski on 15/12/2017.
//

#include "Screen_Stream.h"
#include "Pixel_Stream_Base.h"

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <cassert>


void Screen_Stream::generate_shaders(const std::string &vertex_shader_src, const std::string &frag_shader_src) {
    m_shader = std::make_shared<Shader>(vertex_shader_src.c_str(), frag_shader_src.c_str());
}



Screen_Stream::Screen_Stream(std::shared_ptr<Screen<int>>& screen_dimensions, const std::string& vertex_shader_src, const std::string& frag_shader_src) :
Pixel_Stream_Base(screen_dimensions) {
    init_glfw();

    m_window = create_glfw_window("Raymarcher", screen_dimensions->get_x_max() - screen_dimensions->get_x_min(), screen_dimensions->get_y_max() - screen_dimensions->get_y_min());
    glfwMakeContextCurrent(m_window);

    init_glad();

// Set the viewport size and resize function
    glViewport(0, 0, screen_dimensions->get_x_max() - screen_dimensions->get_x_min(), screen_dimensions->get_y_max() - screen_dimensions->get_y_min());
    glfwSetFramebufferSizeCallback(m_window,
                                   [](GLFWwindow* window, int width, int height) {
                                       glViewport(0, 0, width, height);
                                   }
    );
}




Screen_Stream::~Screen_Stream() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}




void Screen_Stream::flush() {


    glClear(GL_COLOR_BUFFER_BIT);
    //assert(glGetError() != GL_NO_ERROR);

    // Reset texture
    glBindTexture(GL_TEXTURE_2D, m_screen_tex);
    //assert(glGetError() != GL_NO_ERROR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bounds->width(), bounds->height(), 0, GL_RGB, GL_BYTE, &get_buffer()[0]);
    //assert(glGetError() != GL_NO_ERROR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //assert(glGetError() != GL_NO_ERROR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //assert(glGetError() != GL_NO_ERROR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //assert(glGetError() != GL_NO_ERROR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //assert(glGetError() != GL_NO_ERROR);

    // Draw rectangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //assert(glGetError() != GL_NO_ERROR);

    // Used to swap buffers here

    clear();
}

void Screen_Stream::clear() {
    // Reset iterator
    pos_iter = get_buffer().begin();
}

bool Screen_Stream::should_window_close() const {
    return glfwWindowShouldClose(m_window);
}

bool Screen_Stream::key_pressed(int key) const {
    if(glfwGetKey(m_window, key) == GLFW_PRESS)
        return true;

    return false;
}

void Screen_Stream::set_window_should_close(bool value) {
    glfwSetWindowShouldClose(m_window, value);
}

void Screen_Stream::swap_buffers() const {
    glfwSwapBuffers(m_window);
}

void Screen_Stream::poll_events() const {
    glfwPollEvents();
}

void Screen_Stream::init_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

GLFWwindow* Screen_Stream::create_glfw_window(const std::string &window_title, int window_width, int window_height) {
    GLFWwindow* window;
    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW m_window");
    }
    return window;
}

void Screen_Stream::init_glad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}