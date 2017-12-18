#ifndef OPENGL_BOILERPLATE_SHADER_H
#define OPENGL_BOILERPLATE_SHADER_H

#include "NonCopyable.h"

#include <glad/glad.h>
#include <memory>
#include <string>

class Shader : public Util::NonCopyable {
public:
    // The program ID
    GLuint m_ID;

    // References counter
    std::shared_ptr<unsigned int> references;

    // R-value constructor
    Shader(Shader&&);

    // Destructor
    ~Shader();

    // Copy operator
    Shader& operator= (Shader&& rhs);

    // constructor reads and builds the shader
    Shader(const GLchar* vertex_path, const GLchar* fragment_path);

    // use/activate the shader
    void use();

    // utility uniform functions
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

};




#endif //OPENGL_BOILERPLATE_SHADER_H
