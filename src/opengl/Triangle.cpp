#include "Triangle.hpp"

Triangle::Triangle()
: m_shader("shaders/color.vert", "shaders/color.frag")
{
    GLfloat vertices[] = {
            // Positions         // Colors
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   // Bottom Right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f    // Top
    };

    GLuint indices[] = {
            0, 1, 2,  // First Triangle
    };

    glGenVertexArrays(1, &m_vaoId);
    glGenBuffers(1, &m_vboId);
    glGenBuffers(1, &m_eboId);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(m_vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently
    // bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    // remember: do NOT unbind the EBO, keep it bound to this VAO
    glBindVertexArray(0);
    OpenGLError error;
    error.checkOpenGLError("Error init model");
}

void Triangle::draw()
{
    // Draw our first triangle
    m_shader.use();
    glBindVertexArray(m_vaoId); // Bind our Vertex Array Object
    //glDrawArrays(GL_TRIANGLES, 0, 3); <- when not using ebo
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // Unbind our Vertex Array Object

    OpenGLError error;
    error.checkOpenGLError("Error drawing");
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &m_vaoId);
    glDeleteBuffers(1, &m_vboId);
    glDeleteBuffers(1, &m_eboId);
}