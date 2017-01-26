#include "TextureArray.hpp"

TextureArray::TextureArray()
{

}

void TextureArray::addTextures(std::vector<std::string> paths)
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureId);
    int mipLevelCount = 1;
    GLsizei layerCount = (GLsizei) paths.size();
    // glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 16, 16,  layerCount);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    for (auto &path : paths) {
        int width, height, nbChannels;
        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, STBI_rgb_alpha);
        if (image == nullptr) throw(std::string("Failed to load texture"));
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_textureNumber, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
        m_textureNumber ++;
        stbi_image_free(image);
    }

    unbind();
}

GLuint TextureArray::getTextureId() const
{
    return m_textureId;
}

void TextureArray::bind()
{
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureId);
}

void TextureArray::unbind()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::~TextureArray()
{
    glDeleteTextures(1, &m_textureId);
}