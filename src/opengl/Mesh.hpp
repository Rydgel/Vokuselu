#ifndef VOXELS_MESH_HPP
#define VOXELS_MESH_HPP

#include <iostream>
#include <vector>
#include "../../vendors/glad/glad.h"
#include "Vertex.hpp"
#include "TextureArray.hpp"
#include "Shader.hpp"
#include "OpenGLError.hpp"

class Mesh
{
private:
    /*  Mesh Data  */
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    /*  Render data  */
    GLuint m_VAO, m_VBO, m_EBO;
    //
    void setupMesh();
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    void draw(Shader shader);
    void bind();
    void unbind();
    ~Mesh();
};


#endif //VOXELS_MESH_HPP
