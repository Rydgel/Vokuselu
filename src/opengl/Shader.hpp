#ifndef VOXELS_SHADER_HPP
#define VOXELS_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>

class Shader
{
public:
    // The program ID
    GLuint m_program;
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // todo set variables
    // Use the program
    void use();
};


#endif //VOXELS_SHADER_HPP
