#ifndef VOXELS_TEXTURE_HPP
#define VOXELS_TEXTURE_HPP


#include <string>
#include "../../vendors/glad/glad.h"

enum TextureType
{
    Diffuse,
    Spectular
};

static const char *TextureTypeStrings[] =
        {
                "texture_diffuse",
                "texture_spectular",
        };

class Texture
{
public:
    GLuint id;
    TextureType type;
    std::string path;

    static const char *getTextForType(int enumVal);
    Texture(GLuint id, TextureType type, std::string path);
};


#endif //VOXELS_TEXTURE_HPP
