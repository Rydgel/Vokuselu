#include "TextureManager.hpp"

TextureManager::TextureManager()
{
    // empty texture manager
}

void TextureManager::addTexture(const std::string name, const std::string path)
{
    int width, height, nbChannels;
    // todo dynamically check for alpha if needed
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, STBI_rgb);

    if (image == nullptr) throw(std::string("Failed to load texture"));

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (nbChannels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if (nbChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

    // todo param diffuse and shit
    auto textureP = std::make_shared<Texture>(texture, TextureType::Diffuse, path);
    m_textures[name] = textureP;
    // free stuff
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
}

const boost::optional<std::shared_ptr<Texture>> TextureManager::getTexture(const std::string name)
{
    if (m_textures.find(name) != m_textures.end()) {
        return boost::make_optional<std::shared_ptr<Texture>>(
                m_textures[name]
        );
    } else {
        return boost::none;
    }
}

TextureManager::~TextureManager()
{
    for (const auto &map_texture : m_textures) {
        auto texture = map_texture.second;
        glDeleteTextures(1, &texture->id);
    }
}

