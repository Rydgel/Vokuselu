#ifndef VOXELS_MODEL_HPP
#define VOXELS_MODEL_HPP

#include <vector>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include "OpenGLError.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Triangle
{
private:
    GLuint m_vaoId;
    GLuint m_vboId;
    GLuint m_eboId;
    Shader m_shader;
    Mesh m_mesh;

    const std::vector<Vertex> getVertices()
    {
        return {
                Vertex { {0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {}},
                Vertex { {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {}},
                Vertex { {0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {}}
        };
    };

    const std::vector<GLuint> getIndices()
    {
        return { 0, 1, 2 };
    }

    const std::vector<Texture> getTextures()
    {
        return {};
    }
public:
    Triangle();
    void draw();
    ~Triangle();
};


#endif //VOXELS_MODEL_HPP
