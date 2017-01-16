#ifndef VOXELS_MODEL_HPP
#define VOXELS_MODEL_HPP

#include <vector>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include "OpenGLError.hpp"
#include "Shader.hpp"

class Triangle
{
private:
    GLuint m_vaoId;
    GLuint m_vboId;
    GLuint m_eboId;
    Shader m_shader;
public:
    Triangle();
    void draw();
    ~Triangle();
};


#endif //VOXELS_MODEL_HPP
