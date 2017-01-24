#include "AtlasTexture.hpp"

AtlasTexture::AtlasTexture(const std::string path, GLuint size, GLuint textureSize)
: BasicTexture(path)
, m_size(size)
, m_textureSize(textureSize)
{

}

std::vector<GLfloat> AtlasTexture::getTextureCoords(const glm::vec2 &location)
{
    static auto texturesPerRow  = m_size / m_textureSize;
    static auto unitSize = 1.0f / (float) texturesPerRow;

    auto xMin = location.x * unitSize;
    auto yMin = location.y * unitSize;

    auto xMax = xMin + unitSize;
    auto yMax = yMin + unitSize;

    return {
            xMax, yMax,
            xMin, yMax,
            xMin, yMin,
            xMax, yMin
    };

    /*return {
            xMin, yMin,
            xMax, yMin,
            xMax, yMax,
            xMax, yMax,
            xMin, yMax,
            xMin, yMin,
    };*/
}
