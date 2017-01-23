#include "Texture.hpp"

Texture::Texture(GLuint id, TextureType type, std::string path)
: id(id)
, type(type)
, path(path)
{

}

const char *Texture::getTextForType(int enumVal)
{
    return TextureTypeStrings[enumVal];
}
