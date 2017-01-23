#ifndef VOXELS_SHADER_HPP
#define VOXELS_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // The program ID
    GLuint m_program;
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // todo add all uniforms type
    // uniform variable settings
    void setUniform(const std::string &name, GLuint x);
    void setUniform(const std::string &name, int x);
    void setUniform(const std::string &name, float x);
    void setUniform(const std::string &name, glm::mat4 trans);
    // Use the program
    void bind();
    void unbind();
};

// RAII
struct BoundShader
{
    BoundShader(Shader &sh): sh(sh) { sh.bind(); }
    ~BoundShader() { sh.unbind(); }
    Shader &sh;
};
#endif //VOXELS_SHADER_HPP
