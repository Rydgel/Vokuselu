#include "Triangle.hpp"

Triangle::Triangle()
: m_shader("shaders/color.vert", "shaders/color.frag")
, m_mesh(getVertices(), getIndices(), getTextures())
{

}

void Triangle::draw()
{
    // Draw our first triangle
    BoundShader bound(m_shader);
    m_shader.setUniform("hue_value", (float) glfwGetTime());
    m_mesh.draw(m_shader);
}
