#ifndef VOXELS_TEXTURE_HPP
#define VOXELS_TEXTURE_HPP


#include <string>
#include "../../vendors/glad/glad.h"

struct Texture
{
    GLuint id;
    std::string type;
    std::string path;
};


#endif //VOXELS_TEXTURE_HPP
