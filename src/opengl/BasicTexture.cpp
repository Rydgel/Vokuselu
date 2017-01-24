#include "BasicTexture.hpp"

BasicTexture::BasicTexture(const std::string path)
{
    int width, height, nbChannels;

    // todo dynamically check for alpha if needed
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, STBI_rgb_alpha);

    if (image == nullptr)
        throw(std::string("Failed to load texture"));

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

    // free stuff
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
}

BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}

void BasicTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void BasicTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

