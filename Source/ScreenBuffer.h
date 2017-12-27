// 
// Created by Balajanovski on 15/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SCREEN_STREAM_H
#define SIMPLE_RAYTRACER_SCREEN_STREAM_H

#include "PixelBufferBase.h"
#include "Util/Shader.h"
#include "Screen.h"

#include "Includes/glad.h"
#include <GLFW/glfw3.h>
#include <memory>

class ScreenBuffer : public PixelBufferBase {
public:
    ScreenBuffer(Screen<int>* screen_dimensions,
                  const std::string& vertex_shader_src,
                  const std::string& frag_shader_src);
    virtual ~ScreenBuffer() override;

    void make_current() {
        glfwMakeContextCurrent(m_window);
    }

    virtual void flush() override;
    virtual void clear() override;

    // Exposed GLFW functions
    bool should_window_close() const;
    bool key_pressed(int key) const;
    void set_window_should_close(bool value);
    void swap_buffers() const;
    void poll_events() const;

    static void init_glfw();
    static GLFWwindow* create_glfw_window(const std::string &window_title, int window_width, int window_height);
    static void init_glad();
private:
    // Pointer to glfw window
    GLFWwindow *m_window;

    // Texture where pixels are written to
    GLuint m_screen_tex;

    // Shader program
    std::shared_ptr<Shader> m_shader;

    // VAO
    GLuint m_vao;

    // Element buffer object
    GLuint m_ebo;

    // Vertex buffer object
    GLuint m_vbo;

    inline void generate_shaders(const std::string&, const std::string&);
};


#endif //SIMPLE_RAYTRACER_SCREEN_STREAM_H
