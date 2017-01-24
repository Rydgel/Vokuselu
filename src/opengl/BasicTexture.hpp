#ifndef VOXELS_BASICTEXTURE_HPP
#define VOXELS_BASICTEXTURE_HPP

#include <iostream>
#include "../../vendors/stb_image/stb_image.hpp"
#include "../../vendors/glad/glad.h"

class BasicTexture
{
private:
    GLuint m_id;
public:
    BasicTexture(const std::string path);
    void bind();
    void unbind();
    ~BasicTexture();
};

// todo RAII

#endif //VOXELS_BASICTEXTURE_HPP
