#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<Texture>> textures)
: m_vertices(vertices)
, m_indices(indices)
, m_textures(textures)
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
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    OpenGLError error;
    error.checkOpenGLError("Error init model");
}

void Mesh::draw(Shader shader)
{
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        // Retrieve texture number (the N in diffuse_textureN)
        GLuint number = 0;
        TextureType name = m_textures[i]->type;
        if (name == TextureType::Diffuse)
            number = diffuseNr++; // Transfer GLuint to stream
        else if(name == TextureType::Spectular)
            number = specularNr++; // Transfer GLuint to stream
        // Now set the sampler to the correct texture unit
        // todo remove cast by making a new uniform method
        shader.setUniform((name + Texture::getTextForType(number)), (int) i);
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i]->id);
    }

    // Also set each mesh's shininess property to a default value
    // (if you want you could extend this to another mesh property and possibly change this value)
    shader.setUniform("material.shininess", 16.0f);

    // Draw mesh
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLError error;
    error.checkOpenGLError("Error drawing");
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}
