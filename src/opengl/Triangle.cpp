#include "Triangle.hpp"

Triangle::Triangle(TextureManager &textureManager)
: m_shader("shaders/texture.vert", "shaders/texture.frag")
, m_textureManager(textureManager)
, m_mesh(getVertices(), getIndices(), getTextures())
{

}

const std::vector<Vertex> Triangle::getVertices()
{
    return {
            Vertex { {0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            Vertex { {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {5.0f, 0.0f}},
            Vertex { {0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {2.5f, 5.0f}}
    };
}

const std::vector<GLuint> Triangle::getIndices()
{
    return { 0, 1, 2 };
}

const std::vector<std::shared_ptr<Texture>> Triangle::getTextures()
{
    auto pogChampOpt = m_textureManager.getTexture("pogchamp");
    if (pogChampOpt) {
        return { pogChampOpt.get() };
    } else {
        printf("Warning no triangle textures\n");
        return {};
    }
}

void Triangle::draw()
{
    // Draw our first triangle
    glm::mat4 trans;
    // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (GLfloat) glfwGetTime() * 3.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    GLfloat scaleAmount = (float) sin(glfwGetTime());
    trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

    BoundShader bound(m_shader);
    m_shader.setUniform("hue_value", (float) glfwGetTime() * 30);
    m_shader.setUniform("transform", trans);
    m_mesh.draw(m_shader);
}