#ifndef VOXELS_MODEL_HPP
#define VOXELS_MODEL_HPP

#include <vector>
#include "../../vendors/glad/glad.h"

class Model
{
private:
    GLuint m_vaoId;
    GLuint m_vboId;
    GLuint m_eboId;
    GLuint m_shaderProgram;
public:
    Model(const std::vector<GLfloat>& vertexPositions);
    void draw();
    ~Model();
};


#endif //VOXELS_MODEL_HPP
