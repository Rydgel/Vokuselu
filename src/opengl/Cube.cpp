#include "Cube.hpp"

Cube::Cube(TextureManager &textureManager)
: m_shader("shaders/cube_texture.vert", "shaders/cube_texture.frag")
, m_textureManager(textureManager)
, m_mesh(getVertices(), getIndices(), getTextures())
{

}

const std::vector<Vertex> Cube::getVertices()
{
    return {
        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {0.5f, -0.5f, -0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {-0.5f,  0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 0.0f} },

        Vertex { {-0.5f, -0.5f, 0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {0.5f, -0.5f, 0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {0.5f,  0.5f, 0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {0.5f,  0.5f,  0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {-0.5f,  0.5f,  0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {-0.5f, -0.5f,  0.5f}, {}, {0.0f, 0.0f} },

        Vertex { {-0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {-0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {-0.5f, -0.5f,  0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {-0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0f} },

        Vertex { {0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {0.5f, -0.5f,  0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0f} },

        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {0.5f, -0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {0.5f, -0.5f,  0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {0.5f, -0.5f,  0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {-0.5f, -0.5f,  0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {-0.5f, -0.5f, -0.5f}, {}, {0.0f, 1.0f} },

        Vertex { {-0.5f,  0.5f, -0.5f}, {}, {0.0f, 1.0f} },
        Vertex { {0.5f,  0.5f, -0.5f}, {}, {1.0f, 1.0f} },
        Vertex { {0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0f} },
        Vertex { {0.5f,  0.5f,  0.5f}, {}, {1.0f, 0.0} },
        Vertex { {-0.5f,  0.5f,  0.5f}, {}, {0.0f, 0.0f} },
        Vertex { {-0.5f,  0.5f, -0.5f}, {}, {0.0f, 1.0f} },
    };
}

const std::vector<GLuint> Cube::getIndices()
{
    std::vector<GLuint> indices;

    for (GLuint i = 0; i < 36; i ++)
        indices.push_back(i);

    return indices;
}

const std::vector<std::shared_ptr<Texture>> Cube::getTextures()
{
    auto lirikNOpt = m_textureManager.getTexture("lirikN");
    if (lirikNOpt) {
        return { lirikNOpt.get() };
    } else {
        printf("Warning no cube textures\n");
        return {};
    }
}

void Cube::draw()
{
    BoundShader bound(m_shader);
    m_mesh.draw(m_shader);
}

void Cube::draw(glm::mat4 view, glm::mat4 model, glm::mat4 projection)
{
    BoundShader bound(m_shader);
    m_shader.setUniform("view", view);
    m_shader.setUniform("projection", projection);
    m_shader.setUniform("model", model);
    m_mesh.draw(m_shader);
}
