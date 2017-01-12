#ifndef VOXELS_MODEL_HPP
#define VOXELS_MODEL_HPP

#include <vector>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include "Shader.hpp"

class Model
{
private:
    GLuint m_vaoId;
    GLuint m_vboId;
    GLuint m_eboId;
    Shader m_shader;
public:
    Model(const std::vector<GLfloat>& vertexPositions);
    void draw();
    ~Model();
};


#endif //VOXELS_MODEL_HPP
