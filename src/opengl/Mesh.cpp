#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
: m_vertices(vertices)
, m_indices(indices)
{
    setupMesh();
}

void Mesh::setupMesh()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, TexCoords));

    unbind();

    OpenGLError error;
    error.checkOpenGLError("Error init model");
}

void Mesh::makeInstanceBuffer(std::vector<glm::mat4> positions, std::vector<int> layers)
{
    glDeleteBuffers(1, &m_instanceVBO);
    glDeleteBuffers(1, &m_instanceVBOLayouts);
    bind();
    GLsizei vec4Size = sizeof(glm::vec4);
    glGenBuffers(1, &m_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * positions.size(), &positions[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (const void *) 0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (const void *) (vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (const void *) (2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (const void *) (3 * vec4Size));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glGenBuffers(1, &m_instanceVBOLayouts);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBOLayouts);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * layers.size(), &layers[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBOLayouts);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(int), (const void *) 0);
    glEnableVertexAttribArray(7);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(7, 1);

    m_currentPositionsNumber = (int) positions.size();
    unbind();
}

void Mesh::draw(Shader shader)
{
    bind();
    // Draw mesh
    // glBindVertexArray(m_VAO);
    // glDrawElements(GL_TRIANGLES, (GLsizei) m_indices.size(), GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);

    glDrawElementsInstanced(GL_TRIANGLES, (GLsizei) m_indices.size(), GL_UNSIGNED_INT, 0, m_currentPositionsNumber);

    unbind();

    OpenGLError error;
    error.checkOpenGLError("Error drawing");
}

void Mesh::bind()
{
    glBindVertexArray(m_VAO);
}

void Mesh::unbind()
{
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    unbind();
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_instanceVBO);
    glDeleteBuffers(1, &m_instanceVBOLayouts);
}