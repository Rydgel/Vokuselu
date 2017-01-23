#ifndef VOXELS_TRIANGLE_HPP
#define VOXELS_TRIANGLE_HPP

#include <vector>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../../vendors/stb_image/stb_image.hpp"
#include "OpenGLError.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "TextureManager.hpp"
#include "IModel.hpp"

class Triangle : public IModel
{
private:
    Shader m_shader;
    TextureManager &m_textureManager;
    Mesh m_mesh;

    virtual const std::vector<Vertex> getVertices();
    virtual const std::vector<GLuint> getIndices();
    virtual const std::vector<std::shared_ptr<Texture>> getTextures();
public:
    Triangle(TextureManager &textureManager);
    void draw();
    ~Triangle() {};
};


#endif //VOXELS_TRIANGLE_HPP
