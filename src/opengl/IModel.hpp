#ifndef VOXELS_IMODEL_HPP
#define VOXELS_IMODEL_HPP

#include <vector>
#include "Vertex.hpp"
#include "../../vendors/glad/glad.h"
#include "TextureArray.hpp"

class IModel
{
protected:
    virtual const std::vector<Vertex> getVertices() = 0;
    virtual const std::vector<GLuint> getIndices() = 0;
};

#endif //VOXELS_IMODEL_HPP
