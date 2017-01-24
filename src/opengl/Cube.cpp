#include "Cube.hpp"

Cube::Cube(TextureManager &textureManager)
: m_shader("shaders/cube_texture.vert", "shaders/cube_texture.frag")
, m_textureManager(textureManager)
, m_mesh(getVertices(), getIndices(), getTextures())
{

}

const std::vector<Vertex> Cube::getVertices()
{
    std::vector<GLfloat> textureCoords;
    AtlasTexture atlas("resources/textures/terrain.png", 256, 16);
    auto coords = atlas.getTextureCoords({3, 0});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    coords = atlas.getTextureCoords({3, 0});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    coords = atlas.getTextureCoords({3, 0});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    coords = atlas.getTextureCoords({3, 0});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    coords = atlas.getTextureCoords({1, 9});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());
    coords = atlas.getTextureCoords({2, 0});
    textureCoords.insert(textureCoords.end(), coords.begin(), coords.end());

    std::vector<Vertex> vertexes =  {
        Vertex { {1, 0, 0}, {}, {} },
        Vertex { {0, 0, 0}, {}, {} },
        Vertex { {0, 1, 0}, {}, {} },
        Vertex { {1, 1, 0}, {}, {} },

        Vertex { {1, 0, 1}, {}, {} },
        Vertex { {1, 0, 0}, {}, {} },
        Vertex { {1, 1, 0}, {}, {} },
        Vertex { {1, 1, 1}, {}, {} },

        Vertex { {0, 0, 1}, {}, {} },
        Vertex { {1, 0, 1}, {}, {} },
        Vertex { {1, 1, 1}, {}, {} },
        Vertex { {0, 1, 1}, {}, {} },

        Vertex { {0, 0, 0}, {}, {} },
        Vertex { {0, 0, 1}, {}, {} },
        Vertex { {0, 1, 1}, {}, {} },
        Vertex { {0, 1, 0}, {}, {} },

        Vertex { {0, 1, 1}, {}, {} },
        Vertex { {1, 1, 1}, {}, {} },
        Vertex { {1, 1, 0}, {}, {} },
        Vertex { {0, 1, 0}, {}, {} },

        Vertex { {0, 0, 0}, {}, {} },
        Vertex { {1, 0, 0}, {}, {} },
        Vertex { {1, 0, 1}, {}, {} },
        Vertex { {0, 0, 1}, {}, {} },
    };

    int i = 0;
    for (auto &vertex : vertexes) {
        vertexes[i / 2].TexCoords = { textureCoords[i], textureCoords[i + 1] };
        i += 2;
    }

    return vertexes;
}

const std::vector<GLuint> Cube::getIndices()
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

const std::vector<std::shared_ptr<Texture>> Cube::getTextures()
{
    auto textures = m_textureManager.getTexture("terrain");

    if (textures) {
        return { textures.get() };
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
