#ifndef VOXELS_OPENGLERROR_HPP
#define VOXELS_OPENGLERROR_HPP

#include <iostream>
#include "../../vendors/glad/glad.h"

class OpenGLError
{
private:
    const char* glErrorString(GLenum err);
public:
    bool isOpenGLError();
    void checkOpenGLError(std::string error);
};


#endif //VOXELS_OPENGLERROR_HPP
