#ifndef VOXELS_CUBE_HPP
#define VOXELS_CUBE_HPP

#include <vector>
#include "../../vendors/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IModel.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "TextureManager.hpp"

class Cube : public IModel
{
private:
    Shader m_shader;
    TextureManager &m_textureManager;
    Mesh m_mesh;

    virtual const std::vector<Vertex> getVertices();
    virtual const std::vector<GLuint> getIndices();
    virtual const std::vector<std::shared_ptr<Texture>> getTextures();
public:
    Cube(TextureManager &textureManager);
    void draw();
    void draw(glm::mat4 view, glm::mat4 model, glm::mat4 projection);
    ~Cube() {};
};


#endif //VOXELS_CUBE_HPP
