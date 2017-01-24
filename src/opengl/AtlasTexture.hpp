#ifndef VOXELS_ATLASTEXTURE_HPP
#define VOXELS_ATLASTEXTURE_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BasicTexture.hpp"

class AtlasTexture : public BasicTexture
{
public:
    AtlasTexture(const std::string path, GLuint size, GLuint textureSize);
    std::vector<GLfloat> getTextureCoords (const glm::vec2& location);
private:
    GLuint m_size;
    GLuint m_textureSize;
public:

};


#endif //VOXELS_ATLASTEXTURE_HPP
