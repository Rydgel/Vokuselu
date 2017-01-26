#include "CubeModel.hpp"

CubeModel::CubeModel(TextureArray &textureArray)
: m_shader("shaders/cube_texture.vert", "shaders/cube_texture.frag")
, m_textureArray(textureArray)
, m_mesh(getVertices(), getIndices())
{
    m_mesh.bind();
    m_textureArray.bind();
    m_shader.bind();
}

const std::vector<Vertex> CubeModel::getVertices()
{
    return {
        Vertex { {1, 0, 0}, {}, {1, 1, 0} },
        Vertex { {0, 0, 0}, {}, {0, 1, 0} },
        Vertex { {0, 1, 0}, {}, {0, 0, 0} },
        Vertex { {1, 1, 0}, {}, {1, 0, 0} },

        Vertex { {1, 0, 1}, {}, {1, 1, 0} },
        Vertex { {1, 0, 0}, {}, {0, 1, 0} },
        Vertex { {1, 1, 0}, {}, {0, 0, 0} },
        Vertex { {1, 1, 1}, {}, {1, 0, 0} },

        Vertex { {0, 0, 1}, {}, {1, 1, 0} },
        Vertex { {1, 0, 1}, {}, {0, 1, 0} },
        Vertex { {1, 1, 1}, {}, {0, 0, 0} },
        Vertex { {0, 1, 1}, {}, {1, 0, 0} },

        Vertex { {0, 0, 0}, {}, {1, 1, 0} },
        Vertex { {0, 0, 1}, {}, {0, 1, 0} },
        Vertex { {0, 1, 1}, {}, {0, 0, 0} },
        Vertex { {0, 1, 0}, {}, {1, 0, 0} },

        Vertex { {0, 1, 1}, {}, {1, 1, 2} },
        Vertex { {1, 1, 1}, {}, {0, 1, 2} },
        Vertex { {1, 1, 0}, {}, {0, 0, 2} },
        Vertex { {0, 1, 0}, {}, {1, 0, 2} },

        Vertex { {0, 0, 0}, {}, {1, 1, 1} },
        Vertex { {1, 0, 0}, {}, {0, 1, 1} },
        Vertex { {1, 0, 1}, {}, {0, 0, 1} },
        Vertex { {0, 0, 1}, {}, {1, 0, 1} },
    };
}

const std::vector<GLuint> CubeModel::getIndices()
{
    return {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
    };
}


void CubeModel::draw(glm::mat4 view, glm::mat4 model, glm::mat4 projection, int textureLayer)
{
    m_shader.setUniform("view", view);
    m_shader.setUniform("projection", projection);
    m_shader.setUniform("model", model);
    m_shader.setUniform("layer", textureLayer);
    m_mesh.draw(m_shader);
}

CubeModel::~CubeModel()
{
    m_mesh.unbind();
    m_shader.unbind();
    m_textureArray.unbind();
}
