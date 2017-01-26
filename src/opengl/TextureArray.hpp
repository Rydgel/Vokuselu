#ifndef VOXELS_TEXTUREARRAY_HPP
#define VOXELS_TEXTUREARRAY_HPP


#include <vector>
#include <iostream>
#include "../../vendors/stb_image/stb_image.hpp"
#include "../../vendors/glad/glad.h"

class TextureArray
{
private:
    GLuint m_textureId = 0;
    int m_textureNumber = 0;
public:
    TextureArray();
    void addTextures(std::vector<std::string> paths);
    GLuint getTextureId() const;
    void bind();
    void unbind();
    ~TextureArray();
};

// RAII
struct BoundTexture
{
    BoundTexture(TextureArray &ta): ta(ta) { ta.bind(); }
    ~BoundTexture() { ta.unbind(); }
    TextureArray &ta;
};

#endif //VOXELS_TEXTUREARRAY_HPP
