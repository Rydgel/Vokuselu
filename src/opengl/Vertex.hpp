#ifndef VOXELS_VERTEX_HPP
#define VOXELS_VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
};


#endif //VOXELS_VERTEX_HPP
