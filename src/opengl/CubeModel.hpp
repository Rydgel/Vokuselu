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
#include "TextureArray.hpp"

class CubeModel : public IModel
{
private:
    Shader m_shader;
    TextureArray &m_textureArray;
    Mesh m_mesh;

    virtual const std::vector<Vertex> getVertices();
    virtual const std::vector<GLuint> getIndices();
public:
    CubeModel(TextureArray &textureArray);
    void draw(glm::mat4 view, glm::mat4 projection);
    void draw(glm::mat4 view, glm::mat4 model, glm::mat4 projection, int textureLayer);
    void bindPosition(std::vector<glm::mat4> positions, std::vector<int> layers);
    ~CubeModel();
};


#endif //VOXELS_CUBE_HPP
